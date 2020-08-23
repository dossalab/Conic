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
#include <misc/stuff.h>

static volatile DECLARE_LIST(task_list);

static inline struct task *node_to_task(struct list_node *node) {
	return container_of(node, struct task, node);
}

static inline struct list_node *task_to_node(struct task *t) {
	return &t->node;
}

/*
 * this one is irq itself hence it does not need this __disable_irq /
 * __enable_irq stuff
 */
static void tasks_tick_handler(void)
{
	struct list_node *ptr;
	struct task *t;

	list_forward(ptr, &task_list) {
		t = node_to_task(ptr);
		t->counter++;
	}
}

void task_init(struct task *t, void (*handler)(void), uint16_t interval)
{
	bool irq_was_enabled;

	list_init_node(&t->node);
	t->handler = handler;
	t->interval = interval;

	irq_was_enabled = irq_disable();

	list_add_after(&task_list, task_to_node(t));

	if (irq_was_enabled) {
		irq_enable();
	}
}

void tasks_update(void)
{
	struct list_node *ptr;
	struct task *t;
	bool irq_was_enabled;

	irq_was_enabled = irq_disable();

	list_forward(ptr, &task_list) {
		t = node_to_task(ptr);

		if (t->counter >= t->interval) {
			t->handler();
			t->counter = 0;
		}
	}

	if (irq_was_enabled) {
		irq_enable();
	}
}

void task_system_init(void)
{
	arch_timer_init(tasks_tick_handler);
}

