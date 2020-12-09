/*
 * Part of the Conic project - robot arm controller
 *
 * External commands handler
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <core/serial.h>
#include <core/mm.h>
#include <misc/ring.h>
#include <arch/common.h>
#include <mcu/common.h>
#include <misc/crc7.h>
#include <misc/stuff.h>
#include <proto/packet.h>
#include <proto/messages.h>

static DECLARE_RING(input_ring, SERIAL_PACKET_SIZE);
static atomic_flag_t packet_empty;
struct serial_packet received_packet;

/*
 * This handler is called from interrupt, hence we're unable to
 * parse packet and execute commands right away.
 */
static void uart_receive_handler(uint8_t byte)
{
	ring_push(&input_ring, byte);

	/* check if ring contains valid packet */
	if (ring_start(&input_ring) == 0xFF && ring_end(&input_ring) == 0xFF) {
		ring_copy(&input_ring, (uint8_t *)&received_packet, \
					SERIAL_PACKET_SIZE);
		atomic_flag_clr(&packet_empty);
	}
}

static void send_answer(int8_t answer)
{
	struct serial_packet packet;
	struct answer_payload *payload;

	packet_fill(&packet, DEVICE_ANSWER_PID);

	payload = (struct answer_payload *)packet.data;
	payload->retval = answer;

	uart_send((uint8_t *)&packet, sizeof(packet));
}

static int8_t execute_servo_init(struct serial_packet *packet)
{
	struct servo_init_payload *payload;
	struct gpio *port;

	payload = (struct servo_init_payload *)packet->data;
	port = gpio_lookup_by_name(payload->port);

	if (!port) {
		return -1;
	}

	return mm_create_servo(port, payload->pin);
}

static int8_t execute_servo_move(struct serial_packet *packet)
{
	struct servo_move_payload *payload;

	payload = (struct servo_move_payload *)packet->data;

	return mm_move_servo(payload->servo, payload->pulse);
}

static int8_t execute_motion(struct serial_packet *p)
{
	return mm_execute_motion();
}

void serial_execute_pending(void)
{
	if (!atomic_flag_fetch_and_set(&packet_empty)) {
		switch (received_packet.type) {
		case CHECK_PRESENSE_PID:
			send_answer(0);
			break;

		case SERVO_INIT_PID:
			send_answer(execute_servo_init(&received_packet));
			break;

		case SERVO_MOVE_PID:
			send_answer(execute_servo_move(&received_packet));
			break;

		case EXECUTE_MOTION_PID:
			send_answer(execute_motion(&received_packet));
			break;
		}
	}
}

void serial_system_init(void)
{
	atomic_flag_fetch_and_set(&packet_empty);
	uart_on_receive(uart_receive_handler);
}

