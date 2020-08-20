/*
 * Part of the Conic project - robot arm controller
 *
 * Servo driver
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef DRIVERS_SERVO_H
#define DRIVERS_SERVO_H

#include <stdint.h>
#include <mcu/common.h>
#include <misc/list.h>

#define SERVO_PERIOD		20000U	/* 20 ms, or 50 Hz */

/*
 * Glue servos with value less than this threshold together
 *
 * This value really depends on a clock rate but obviously we cannot interrupt 
 * every microsecond and hope that mcu will be fine
 *
 * So we glue simular values together, still maintaining reasonable
 * accuracy (14 us is like ~1% from typical 1000 us control pulse)
 */
#define SERVO_DUPLICATE_VALUE	14

struct servo {
	struct list_node node;
	uint16_t position;

	/* data line */
	struct gpio *port;
	uint8_t pin;
};

void servo_set(struct servo *s, uint16_t position);
void servo_init(struct servo *s, struct gpio *port, uint8_t pin);
void servo_system_init(void);

#endif

