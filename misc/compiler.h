/*
 * Part of the Conic project - robot arm controller
 *
 * Currently only GCC. ONLY GCC :)
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef MISC_COMPILER_H
#define MISC_COMPILER_H

#define place_section(section_name) \
	__attribute__((used, section(section_name)))

#define __weak __attribute__((weak))

#endif

