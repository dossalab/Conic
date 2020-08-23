/*
 * Part of the Conic project - robot arm controller
 *
 * Common ARCH api
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <stdbool.h>

static inline void irq_enable(void);
static inline bool irq_disable(void);

/* Setup 1 ms resolution timer for task manager */
void arch_timer_init(void (*timer_handler)(void));

#include ARCH_SPECIFIC_HEADER

