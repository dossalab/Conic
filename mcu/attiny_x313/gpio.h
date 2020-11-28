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

