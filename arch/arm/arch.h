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

#include <stdint.h>

typedef uint32_t atomic_flag_t;

static inline void irq_enable(void)
{
	asm volatile ("cpsie i" ::: "memory", "cc");
}

static inline bool irq_disable(void)
{
	uint32_t saved_primask;

	asm volatile(
		"mrs %0, primask\n"
		"cpsid i"
		: "=r" (saved_primask) :: "memory", "cc");

	return !saved_primask;
}

static inline atomic_flag_t atomic_flag_fetch_and_set(atomic_flag_t *flag)
{
	return __sync_fetch_and_or(flag, 1);
}

static inline void atomic_flag_clr(atomic_flag_t *flag)
{
	__sync_fetch_and_and(flag, 0);
}

#endif

