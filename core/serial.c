/*
 * Part of the Conic project - robot arm controller
 *
 * External commands handler
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <core/serial.h>
#include <misc/ring.h>
#include <arch/common.h>
#include <core/arm.h>
#include <mcu/common.h>
#include <misc/crc7.h>
#include <misc/stuff.h>
#include <proto/packet.h>
#include <proto/messages.h>

static DECLARE_RING(input_ring, SERIAL_PACKET_SIZE);
static atomic_flag_t packet_filled;
static struct serial_packet received_packet;

/*
 * This handler is called from interrupt, hence we're unable to
 * parse packet and execute commands right away.
 */
static void uart_receive_irq(uint8_t byte)
{
	ring_push(&input_ring, byte);

	if (atomic_flag_read(&packet_filled)) {
		/* just drop it? */
		return;
	}

	/* check if ring contains valid packet */
	if (ring_start(&input_ring) == 0xFF && ring_end(&input_ring) == 0xFF) {
		ring_copy(&input_ring, (uint8_t *)&received_packet, \
					SERIAL_PACKET_SIZE);
		atomic_flag_set(&packet_filled);
	}
}

static void handle_move_packet(struct serial_packet *packet)
{
	struct move_packet_payload *payload = (void *)packet->data;
	move_packet_handle(payload);
}

void serial_execute_pending(void)
{
	if (atomic_flag_read(&packet_filled)) {
		switch (received_packet.type) {
		case MOVE_PACKET_ID:
			handle_move_packet(&received_packet);
			break;
		}

		atomic_flag_clr(&packet_filled);
	}
}

void serial_system_init(void)
{
	atomic_flag_clr(&packet_filled);
	uart_on_receive(uart_receive_irq);
}

