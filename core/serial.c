/*
 * Part of the Conic project - robot arm controller
 *
 * External commands handler
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <core/tasks.h>
#include <core/serial.h>
#include <misc/ring.h>
#include <arch/common.h>
#include <mcu/common.h>
#include <misc/crc7.h>
#include <misc/stuff.h>

static volatile struct task execute_packet_task;
static volatile DECLARE_RING(input_ring, SERIAL_PACKET_SIZE);
static volatile bool packet_ready = false;
static DECLARE_LIST(packet_handlers);

#define node_to_handler(_node) \
	container_of(_node, struct serial_handler, node)

#define handler_to_node(_handler) \
	&_handler->node

static void proceed_packet(void)
{
	/* volatile should tell compiler not to rearrange any code */
	volatile struct serial_packet packet;
	struct list_node *ptr;
	struct serial_handler *handler;
	bool irq_was_enabled;

	irq_was_enabled = irq_disable();

	if (!packet_ready) {
		/* Nothing to do here... */
		if (irq_was_enabled) {
			irq_enable();
		}

		return;
	}

	ring_copy(&input_ring, (uint8_t *)&packet, SERIAL_PACKET_SIZE);
	packet_ready = false;

	if (irq_was_enabled) {
		irq_enable();
	}

	/* TODO: check CRC here */

	list_forward(ptr, &packet_handlers) {
		handler = node_to_handler(ptr);

		if (handler->packet_type == packet.type) {
			handler->callback(packet.data);
			break;
		}
	}
}

/*
 * This handler is called from interrupt, hence we're unable to
 * parse packet and execute commands right away.
 */
static void uart_receive_handler(uint8_t byte)
{
	if (packet_ready) {
		/* do not overwrite existing packet */
		return;
	}

	ring_push(&input_ring, byte);

	/* check if ring contains valid packet */
	if (ring_start(&input_ring) == 0xFF && ring_end(&input_ring) == 0xFF) {
		packet_ready = true;
	}
}

void serial_handle(struct serial_handler *h, int type, void (*callback)(void *))
{
	list_init_node(handler_to_node(h));
	h->packet_type = type;
	h->callback = callback;

	list_add_after(&packet_handlers, handler_to_node(h));
}

void serial_system_init(void)
{
	uart_on_receive(uart_receive_handler);

	/* Parse packets and execute commands every 100 ms */
	task_init(&execute_packet_task, proceed_packet, 100);

	packet_ready = 0;
}

