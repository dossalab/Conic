/*
 * Part of the Conic project - robot arm controller
 *
 * Servo driver.
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef DRIVERS_SERVO_H
#define DRIVERS_SERVO_H

#include <stdint.h>
#include <mcu/common.h>

#define SERVO_PERIOD		20000U	/* 20 ms, or 50 Hz */
#define SERVO_MIN		1000U	/* 1 ms */
#define SERVO_MAX		2000U	/* 2 ms */

/*
 * We handle gpio so funky because AVR gpio_set / gpio_clr are declared
 * as macro. So we spawn some servo-specific auxilary functions for gpio. Fun!
 */
struct servo {
	uint16_t counter;
	uint16_t position;
	void (*dataline_clr)(void);
	void (*dataline_set)(void);
	void (*dataline_out)(void);
};

#define DECLARE_SERVO(name, port, pin) \
	static inline void servo_##name##_gpio_set(void) { \
		gpio_set(port, pin); \
	} \
	static inline void servo_##name##_gpio_clr(void) { \
		gpio_clr(port, pin); \
	} \
	static inline void servo_##name##_gpio_out(void) { \
		gpio_out(port, pin); \
	} \
	struct servo name = { \
		.position = 1190, \
		.dataline_clr = servo_##name##_gpio_clr, \
		.dataline_set = servo_##name##_gpio_set, \
		.dataline_out = servo_##name##_gpio_out \
	}

void servo_set(struct servo *s, uint16_t position);
void servo_init(struct servo *servos[], uint8_t len);

#endif

