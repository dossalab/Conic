/*
 * Part of the Conic project - robot arm controller
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef MISC_STUFF_H
#define MISC_STUFF_H

#define BIT(X)			(1 << (X))
#define ARRAY_LEN(array)	(sizeof(array) / sizeof(array[0]))

#define container_of(ptr, type, member) ({                      \
	const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
	(type *)( (char *)__mptr - offsetof(type,member) );})

#endif

