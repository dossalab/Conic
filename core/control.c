/*
 * Part of the Conic project - robot arm controller
 *
 * External commands handler
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <core/tasks.h>
#include <core/control.h>
#include <core/arm.h>
#include <misc/endian.h>
#include <misc/ring.h>
#include <arch/common.h>
#include <mcu/common.h>
#include <board/common.h>
#include <misc/crc7.h>
#include <string.h> /* for memcpy */

static volatile struct task execute_packet_task;
static volatile DECLARE_RING(input_ring, PACKET_SIZE);
static volatile bool packet_ready = false;

static bool packet_debug_handler(struct packet *p)
{
	if (p->as_debug.led_on) {
		board_led_on();
	} else {
		board_led_off();
	}

	return 1;
}

static bool packet_motion_handler(struct packet *p)
{
	float x = le32_to_cpu(p->as_motion.x);
	float y = le32_to_cpu(p->as_motion.y);
	float z = le32_to_cpu(p->as_motion.z);
	float a = le32_to_cpu(p->as_motion.a);

	return arm_move(x, y, z, a);
}

static packet_handler_t packet_handlers[] = {
	[PACKET_TYPE_DEBUG] = packet_debug_handler,
	[PACKET_TYPE_MOTION] = packet_motion_handler,
};

static void proceed_packet(void)
{
	/* volatile should tell compiler not to rearrange any code */
	volatile struct packet in_packet;
	bool irq_was_enabled;
	bool ret;

	irq_was_enabled = irq_disable();

	if (packet_ready) {
		ring_copy(&input_ring, (uint8_t *)&in_packet, PACKET_SIZE);

		/* now packet is safely saved and we can somehow react to it... */
		if (in_packet.type >= 0 && in_packet.type < PACKET_TYPE_COUNT) {
			ret = packet_handlers[in_packet.type](&in_packet);

			if (!ret) {
				/* TODO: reply with NACK - unable to complete task */
			}
		}

		packet_ready = false;
	}

	if (irq_was_enabled) {
		irq_enable();
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

void control_init(void)
{
	uart_on_receive(uart_receive_handler);

	/* Parse packets and execute commands every 100 ms */
	task_init(&execute_packet_task, proceed_packet, 100);

	packet_ready = 0;
}

