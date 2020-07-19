/*
 * Part of the Conic project - robot arm controller
 *
 * Simple timer-like tasks manager
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef CORE_TASKS_H
#define CORE_TASKS_H

#include <stdbool.h>

/* Should be no more than 8 because of, well, AVR */
#define MAX_TASKS	8

#include <stdint.h>

int tasks_set(int interval, void (*handler)(void), bool oneshot);
void tasks_proceed(void);

void tasks_init(void);

#endif

