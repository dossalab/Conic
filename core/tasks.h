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

#include <stdint.h>
#include <misc/list.h>

struct task {
	struct list_node node;

	uint16_t interval;
	uint16_t counter;
	void (*handler)(void);
};

void task_init(struct task *t, void (*handler)(void), uint16_t interval);
void tasks_update(void);
void task_system_init(void);

#endif

