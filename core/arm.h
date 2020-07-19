/*
 * Part of the Conic project - robot arm controller
 *
 * Arm motion controller
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef CORE_ARM_H
#define CORE_ARM_H

#include <stdbool.h>

bool arm_move(float x, float y, float z, float a);
void arm_init(void);

#endif

