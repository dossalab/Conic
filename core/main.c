/*
 * Part of the Conic project - robot arm controller
 *
 * Application entry point
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <board/common.h>
#include <core/serial.h>
#include <arch/common.h>
#include <mcu/common.h>
#include <drivers/servo.h>

void main(void)
{
	board_init();
	serial_system_init();
	servo_system_init();

	irq_enable();

	while (1) {
		serial_execute_pending();
	}
}

