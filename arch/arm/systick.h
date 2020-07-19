/*
 * Part of the Conic project - robot arm controller
 *
 * ARM cortex-m SysTick
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef ARCH_ARM_SYSTICK_H
#define ARCH_ARM_SYSTICK_H

#include <stdint.h>

struct systick {
	volatile uint32_t CTRL;
	volatile uint32_t LOAD;
	volatile uint32_t VAL;
	volatile const uint32_t CALIB;
};

#define SYSTICK_BASE	0xE000E010UL
#define SYSTICK		((struct systick *)SYSTICK_BASE)

void arch_timer_init(void (*arch_timer_handler)(void));

#endif

