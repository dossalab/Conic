/*
 * Part of the Conic project - robot arm controller
 *
 * ATtiny2313/4313 GPIO.
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef MCU_ATTINY_X313_GPIO_H
#define MCU_ATTINY_X313_GPIO_H

#include <stdint.h>

/* Not sure about this SFR fuzz but that ones with SFR offset (0x20) */
#define GPIOD_BASE	0x30
#define GPIOB_BASE	0x36
#define GPIOA_BASE	0x39

struct gpio {
	volatile uint8_t PIN;
	volatile uint8_t DDR;
	volatile uint8_t PORT;
};

#define GPIOD	((struct gpio*)GPIOD_BASE)
#define GPIOB	((struct gpio*)GPIOB_BASE)
#define GPIOA	((struct gpio*)GPIOA_BASE)

#endif

