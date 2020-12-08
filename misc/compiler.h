/*
 * Part of the Conic project - robot arm controller
 *
 * Currently only GCC. ONLY GCC :)
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef MISC_COMPILER_H
#define MISC_COMPILER_H

/*
 * Provide a memory barrier to the compiler. That completes all
 * memory operations before the barrier, so the compiler shouldn't
 * re-order any memory access around it
 */
static inline void barrier(void)
{
	asm volatile("" ::: "memory", "cc");
}

#define place_section(section_name) \
	__attribute__((used, section(section_name)))

#define __weak __attribute__((weak))

#endif

