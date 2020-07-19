/*
 * Part of the Conic project - robot arm controller
 *
 * Application entry point
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <mcu/common.h>
#include <arch/common.h>
#include <board/common.h>
#include <core/control.h>
#include <core/arm.h>
#include <core/tasks.h>
#include <stdint.h>

int servo_pos;

static void blink_led(void)
{
	//servo_set(NULL, servo_pos);
	servo_pos += 100;
	uart_printf("hi! %d\n\r", servo_pos);
	if (servo_pos >= 2000) servo_pos = 0;
}

void main(void)
{
	board_init();
	control_init();
	tasks_init();
	arm_init();

	tasks_set(100, blink_led, 0);

	while (1) {
		tasks_proceed();
	}
}

