/*
 * Part of the Conic project - robot arm controller
 *
 * Servo driver
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <drivers/servo.h>
#include <arch/common.h>
#include <misc/stuff.h>

static volatile DECLARE_LIST(servo_list);
static struct list_node *current_node;

static inline struct servo *node_to_servo(struct list_node *node) {
	return container_of(node, struct servo, node);
}

static inline struct list_node *servo_to_node(struct servo *s) {
	return &s->node;
}

static void servo_overflow_handler(void)
{
	struct list_node *ptr;
	struct servo *s;

	list_forward(ptr, &servo_list) {
		s = node_to_servo(ptr);
		gpio_set(s->port, s->pin);
	}

	if ((current_node = list_first(&servo_list))) {
		s = node_to_servo(current_node);
		timer_set_compare(s->position);
	}
}

/* 1-2 ms compare events */
static void servo_compare_handler(void)
{
	struct servo *s;

	if (current_node) {
		s = node_to_servo(current_node);
		gpio_clr(s->port, s->pin);

		/* Load next servo */
		if (list_next_node(&servo_list, &current_node)) {
			s = node_to_servo(current_node);
			timer_set_compare(s->position);
		}
	}
}

void servo_set(struct servo *s, uint16_t position)
{
	struct list_node *ptr;
	struct servo *list_servo;
	bool inserted = false;

	__disable_irq;

	list_delete(servo_to_node(s));
	s->position = position;

	list_forward(ptr, &servo_list) {
		list_servo = node_to_servo(ptr);

		if (s->position < list_servo->position) {
			list_add_before(ptr, servo_to_node(s));
			inserted = true;
			break;
		}
	}

	if (!inserted) {
		/* insert servo at the end */
		list_add_before(&servo_list, servo_to_node(s));
	}

	__enable_irq;
}

void servo_init(struct servo *s, struct gpio *port, uint8_t pin)
{
	list_init_node(&s->node);

	s->port = port;
	s->pin = pin;

	gpio_out(s->port, s->pin);
}

void servo_system_init(void)
{
	timer_on_overflow(servo_overflow_handler);
	timer_on_compare(servo_compare_handler);

	timer_set_overflow(SERVO_PERIOD); /* ~20 ms between overflows */

	/* do not generate compare events until first overflow */
	timer_set_compare(SERVO_PERIOD + 1);

	timer_init();
	timer_start();
}

