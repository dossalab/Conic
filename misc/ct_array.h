/*
 * Part of the Conic project - robot arm controller
 *
 * Compile-time array. Note that type checking is not implemented here (and
 * probably not even possible)
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef MISC_CT_ARRAY_H
#define MISC_CT_ARRAY_H

#include <misc/compiler.h>

#ifdef ARCH_avr
	#error ct_array does not work on AVRs, because of PROGMEM. FIXME!
#endif

#define ct_array_add(name, type, var, value) \
	static type var __attribute__((section(#name))) = value;

#define ct_array_foreach(name, type, elem) \
	for (type *elem = \
		({ \
			extern type __start_##name; \
			&__start_##name; \
		}); \
		elem != \
		({ \
			extern type __stop_##name; \
			&__stop_##name; \
		}); \
		++elem)

#endif

