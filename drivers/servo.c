/*
 * Part of the Conic project - robot arm controller
 *
 * Servo driver.
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <drivers/servo.h>
#include <arch/common.h>

static struct servo **servo_pointers;
static uint8_t servo_count;

/* 20 ms overflow events */
static void servo_overflow_handler(void)
{
	struct servo *s = servo_pointers[0];
	s->dataline_set();
}

/* 1-2 ms compare events */
static void servo_compare_handler(void)
{
	struct servo *s = servo_pointers[0];
	s->dataline_clr();
}

void servo_set(struct servo *s, uint16_t position)
{
	__disable_irq;
	timer_set_compare(position);
	__enable_irq;
}

/*
 * Most servos require 50 Hz PWM, with 1-2 ms pulse
 */
void servo_init(struct servo *servos[], uint8_t len)
{
	struct servo *s;

	servo_pointers = servos;
	servo_count = len;

	for (uint8_t i = 0; i < servo_count; i++) {
		s = servo_pointers[i];
		s->dataline_out();
	}

	timer_on_overflow(servo_overflow_handler);
	timer_on_compare(servo_compare_handler);

	timer_set_overflow(20000); /* 20 ms between overflows */
	timer_set_compare(1000); /* 1 ms compare (servo low) */

	timer_init();
	timer_start();
}

