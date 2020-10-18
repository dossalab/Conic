/*
 * Part of the Conic project - robot arm controller
 *
 * Simplest non-linear optimization library.
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef LIB_OPTIMIZE_H
#define LIB_OPTIMIZE_H

#include <stddef.h>

struct parameter {
	float value;
	float assumption;
	float min, max;
	float scale;
};

#define mkparameter(_min, _max)	\
	(struct parameter){ .min = _min, .max = _max }

typedef float (*forward_func_t)(struct parameter *, size_t count);

void optimize(struct parameter *parameters, size_t count, forward_func_t func);

#endif

