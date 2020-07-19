/*
 * Part of the Conic project - robot arm controller
 *
 * ATMega88/168/328 gpio.
 *
 * Unfortunately, we cannot use definitions from mcu/common.h because the way
 * GPIO works on AVR. So we define here all required functions as hacky macro
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef MCU_ATMEGA_X8_GPIO_H
#define MCU_ATMEGA_X8_GPIO_H

#include <avr/io.h>

/*
 * We need this bridge to let preprocessor fully expand variables,
 * in case port or pin was defined as macro
 */
#define gpio_get(port, pin)	_gpio_get(port, pin)
#define gpio_set(port, pin)	_gpio_set(port, pin)
#define gpio_clr(port, pin)	_gpio_clr(port, pin)
#define gpio_toggle(port, pin)	_gpio_toggle(port, pin)

#define gpio_in(port, pin)	_gpio_in(port, pin)
#define gpio_out(port, pin)	_gpio_out(port, pin)

/* Now actual implementations */
#define _gpio_get(port, pin) \
	!!(PIN##port & (1 << pin))

#define _gpio_set(port, pin) \
	do { \
		PORT##port |= (1 << pin); \
	} while (0)

#define _gpio_clr(port, pin) \
	do { \
		PORT##port &= ~(1 << pin); \
	} while (0)

#define _gpio_toggle(port, pin) \
	do { \
		PORT##port ^= (1 << pin); \
	} while (0)


#define _gpio_in(port, pin) \
	do { \
		DDR##port &= ~(1 << pin); \
	} while (0)

#define _gpio_out(port, pin) \
	do { \
		DDR##port |= (1 << pin); \
	} while (0)

#endif

