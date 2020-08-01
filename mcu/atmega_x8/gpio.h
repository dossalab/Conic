/*
 * Part of the Conic project - robot arm controller
 *
 * ATMega88/168/328 gpio.
 *
 * I am not a huge fan of redefining stuff from <avr/io.h> but it's probably
 * impossible to get api even close to usable with macro like PORTB / DDRB, eh
 *
 * With something like 'struct gpio' we can pass port and pin directly into
 * driver init function
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef MCU_ATMEGA_X8_GPIO_H
#define MCU_ATMEGA_X8_GPIO_H

#include <stdint.h>

/* Not sure about this SFR fuzz but that ones with SFR offset (0x20) */
#define GPIOB_BASE	0x23
#define GPIOC_BASE	0x26
#define GPIOD_BASE	0x29

struct gpio {
	volatile uint8_t PIN;
	volatile uint8_t DDR;
	volatile uint8_t PORT;
};

#define GPIOB	((struct gpio*)GPIOB_BASE)
#define GPIOC	((struct gpio*)GPIOC_BASE)
#define GPIOD	((struct gpio*)GPIOD_BASE)

#endif

