/*
 * Part of the Conic project - robot arm controller
 *
 * Arm motion controller
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef CORE_ARM_H
#define CORE_ARM_H

#include <stdbool.h>
#include <stdint.h>

#define MOVE_PACKET_ID			0x11

struct move_packet_payload {
	int16_t x;
	int16_t y;
	int16_t z;
};

void arm_init(void);

#endif

