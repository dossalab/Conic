/*
 * Part of the Conic project - robot arm controller
 *
 * Serial packets handler
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef CORE_SERIAL_H
#define CORE_SERIAL_H

#include <stdint.h>
#include <stdbool.h>

void serial_execute_pending(void);
void serial_system_init(void);

#endif

