/*
 * Part of the Conic project - robot arm controller
 *
 * Arm motion controller. 5 servos arm, and claw
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <string.h> /* for memset */
#include <stdlib.h> /* for abs */
#include <math.h>
#include <core/arm.h>
#include <core/serial.h>
#include <core/tasks.h>
#include <board/common.h>
#include <drivers/servo.h>
#include <misc/stuff.h>
#include <misc/linmath.h>
#include <misc/endian.h>
#include <proto/messages.h>

static struct servo servo_1;
static struct servo servo_2;
static struct servo servo_3;
static struct servo servo_4;
static struct servo servo_5;
static struct servo servo_6;

static struct serial_handler move_packet_handler;

/*
 * The given angle is in fixed-point radians (0 -> lowest, 6290 -> highest)
 * Also, this is very servo-dependent
 */
static inline uint16_t angle_to_pulse(uint16_t angle)
{
	/* approx 400 - 2400 */
	return angle / 3 + 400;
}

static void move_callback(void *raw_data)
{
	struct move_packet_payload *payload = raw_data;

	payload->s1 = le16_to_cpu(payload->s1);
	payload->s2 = le16_to_cpu(payload->s2);
	payload->s3 = le16_to_cpu(payload->s3);
	payload->s4 = le16_to_cpu(payload->s4);
	payload->s5 = le16_to_cpu(payload->s5);
	payload->s6 = le16_to_cpu(payload->s6);

	servo_set(&servo_1, angle_to_pulse(payload->s1));
	servo_set(&servo_2, angle_to_pulse(payload->s2));
	servo_set(&servo_3, angle_to_pulse(payload->s3));
	servo_set(&servo_4, angle_to_pulse(payload->s4));
	servo_set(&servo_5, angle_to_pulse(payload->s5));
	servo_set(&servo_6, angle_to_pulse(payload->s6));
}

void arm_init(void)
{
	servo_init(&servo_1, BOARD_SERVO_1_PORT, BOARD_SERVO_1_PIN);
	servo_init(&servo_2, BOARD_SERVO_2_PORT, BOARD_SERVO_2_PIN);
	servo_init(&servo_3, BOARD_SERVO_3_PORT, BOARD_SERVO_3_PIN);
	servo_init(&servo_4, BOARD_SERVO_4_PORT, BOARD_SERVO_4_PIN);
	servo_init(&servo_5, BOARD_SERVO_5_PORT, BOARD_SERVO_5_PIN);
	servo_init(&servo_6, BOARD_SERVO_6_PORT, BOARD_SERVO_6_PIN);

	serial_handle(&move_packet_handler, MOVE_PACKET_ID, move_callback);
}

