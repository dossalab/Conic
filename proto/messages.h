/*
 * Part of the Conic project - robot arm controller
 *
 * All of the messages between host and firmware
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef PROTO_MESSAGES_H
#define PROTO_MESSAGES_H

#include <stdio.h>

#define CHECK_PRESENSE_PID	0x15
#define SERVO_INIT_PID		0x17
#define SERVO_MOVE_PID		0x19
#define EXECUTE_MOTION_PID	0x21
#define DEVICE_ANSWER_PID	0x23

/* Messages are padded to 4-byte boundaries */
struct check_presense_payload {
	uint8_t reserved[4];
};

struct servo_init_payload {
	char port;
	uint8_t pin;
	uint8_t reserved[2];
};

struct servo_move_payload {
	uint8_t servo;
	uint16_t pulse;
	uint8_t reserved[1];
};

struct execute_motion_payload {
	uint8_t reserved[4];
};

struct answer_payload {
	int8_t retval;
	uint8_t reserved[3];
};

#endif

