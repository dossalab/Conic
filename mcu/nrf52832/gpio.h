/*
 * Part of the Conic project - robot arm controller
 *
 * NRF52832 gpio support
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef MCU_NRF52832_GPIO_H
#define MCU_NRF52832_GPIO_H

#include <stdint.h>

#define NRF_P0_BASE	0x50000000

struct gpio {
	volatile uint32_t __reserved_0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t LATCH;
	volatile uint32_t DETECTMODE;
	volatile uint32_t __reserved_1[118];
	volatile uint32_t PIN_CNF[32];
};

#define NRF_P0	((struct gpio*)NRF_P0_BASE)

#endif

