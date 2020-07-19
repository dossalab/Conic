/*
 * Part of the Conic project - robot arm controller
 *
 * ARM Cortex-M architecture support. Tested on Cortex-m3/m4
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef ARCH_ARM_ARCH_H
#define ARCH_ARM_ARCH_H

#define __enable_irq \
	do { \
		__asm volatile ("cpsie i" ::: "memory"); \
	} while (0);

#define __disable_irq \
	do { \
		__asm volatile ("cpsid i" ::: "memory"); \
	} while (0);

typedef unsigned int arch_flag_t;

#endif

