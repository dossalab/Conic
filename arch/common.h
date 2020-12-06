/*
 * Part of the Conic project - robot arm controller
 *
 * Common ARCH api
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

/* this already has header guard */
#include ARCH_SPECIFIC_HEADER

#ifndef ARCH_COMMON_H
#define ARCH_COMMON_H

#include <stdbool.h>
#include <misc/compiler.h>

static inline void irq_enable(void);
static inline bool irq_disable(void);

/* Setup 1 ms resolution timer for task manager */
void arch_timer_init(void (*timer_handler)(void));

/* atomic_flag_t is implementation-specific */
static inline void atomic_flag_set(atomic_flag_t *flag)
{
	*flag = 1;
	barrier();
}

static inline void atomic_flag_clr(atomic_flag_t *flag)
{
	*flag = 0;
	barrier();
}

static inline atomic_flag_t atomic_flag_read(atomic_flag_t *flag)
{
	barrier();
	return *flag;
}

#endif
