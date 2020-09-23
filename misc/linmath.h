/*
 * Part of the Conic project - robot arm controller
 *
 * That will be a linear math library later...
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef MISC_LINMATH_H
#define MISC_LINMATH_H

typedef struct {
	int16_t x, y, z;
} vec3;

#define mkvec3(x, y, z) (vec3){x, y, z}

#endif

