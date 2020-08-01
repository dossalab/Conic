/*
 * Part of the Conic project - robot arm controller
 *
 * Simple timer-like tasks manager
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <core/tasks.h>
#include <arch/common.h>

static volatile arch_flag_t task_flags;

volatile struct task {
	unsigned int interval;
	unsigned int counter;
	void (*handler)(void);
	bool oneshot;
} tasks[MAX_TASKS];

static void tasks_tick_handler(void)
{
	for (int i = 0; i < MAX_TASKS; i++) {
		volatile struct task *t = &tasks[i];

		if (t->interval <= 0) {
			continue;
		}

		t->counter--;
		if (t->counter <= 0) {
			task_flags |= (1 << i);

			if (!t->oneshot) {
				t->counter += t->interval;
			} else {
				t->interval = -1;
			}
		}
	}
}

bool tasks_set(int interval, void (*handler)(void), bool oneshot)
{
	__disable_irq;

	for (int i = 0; i < MAX_TASKS; i++) {
		volatile struct task *t = &tasks[i];

		if (t->handler == handler) {
			t->interval = interval;
			t->counter = interval;
			t->oneshot = oneshot;
			return true;
		}
	}

	for (int i = 0; i < MAX_TASKS; i++) {
		volatile struct task *t = &tasks[i];

		if (t->interval <= 0) {
			t->interval = interval;
			t->counter = interval;
			t->handler = handler;
			t->oneshot = oneshot;
			return true;
		}
	}

	__enable_irq;

	return false;
}


void tasks_proceed(void)
{
	volatile arch_flag_t flags;
	volatile arch_flag_t clear_flags;

	__disable_irq;
	flags = task_flags;
	clear_flags = 0;
	__enable_irq;

	for (int i = 0; i < MAX_TASKS; i++) {
		if (flags & (1 << i)) {
			volatile struct task *t = &tasks[i];
			t->handler();
			clear_flags |= (1 << i);
		}
	}

	__disable_irq;
	task_flags &= ~clear_flags;
	__enable_irq;
}

void tasks_init(void)
{
	arch_timer_init(tasks_tick_handler);
	__enable_irq;
}

