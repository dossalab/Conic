/*
 * Part of the Conic project - robot arm controller
 *
 * Application entry point
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <board/common.h>
#include <core/control.h>
#include <core/tasks.h>
#include <core/arm.h>

#include <mcu/common.h>
#include <drivers/servo.h>

void main(void)
{
	board_init();
	control_init();
	servo_system_init();
	tasks_init();
	arm_init();

	while (1) {
		tasks_proceed();
	}
}

