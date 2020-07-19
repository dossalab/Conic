/*
 * Part of the Conic project - robot arm controller
 *
 * AVR support.
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef ARCH_AVR_ARCH_H
#define ARCH_AVR_ARCH_H

#include <avr/interrupt.h>

typedef unsigned char arch_flag_t;

#define __enable_irq \
	do { \
		__asm volatile ("sei" ::: "memory"); \
	} while (0);

#define __disable_irq \
	do { \
		__asm volatile ("cli" ::: "memory"); \
	} while (0);

#endif

