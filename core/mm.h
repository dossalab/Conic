/*
 * Part of the Conic project - robot arm controller
 *
 * Motion / servo manager.
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef CORE_MM_H
#define CORE_MM_H

#include <stdint.h>
#include <stdbool.h>
#include <drivers/servo.h>

struct mm_chunk {
	bool occupied;
	struct servo servo;
};

int8_t mm_create_servo(struct gpio *port, int8_t pin);
int8_t mm_move_servo(int8_t handle, uint16_t pulse);
int8_t mm_execute_motion(void);

void mm_system_init(void);

#endif

