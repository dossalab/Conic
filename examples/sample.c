/*
 * Part of the Conic project - robot arm controller
 *
 * Sample C program that shows how to create some servos and move them.
 * compile with `gcc sample.c -lconic -o sample` after you install the lib
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <libconic.h>
#include <stdarg.h>

static void die(const char *format, ...)
{
	va_list args;

	va_start(args, format);
	vprintf(format, args);
	va_end(args);

	exit(1);
}

int main(void)
{
	int device;
	int servo_1, servo_2, servo_3;

	device = conic_device_open();
	if (device < 0) {
		die("error opening device\n");
	}

	servo_1 = conic_servo_init(device, 'A', 10);
	servo_2 = conic_servo_init(device, 'A', 11);
	servo_3 = conic_servo_init(device, 'A', 12);

	if (servo_1 < 0 || servo_2 < 0 || servo_3 < 0) {
		conic_device_close(device);
		die("unable to create servos\n");
	}

	conic_servo_move(device, servo_1, 1000);
	conic_servo_move(device, servo_2, 1000);
	conic_servo_move(device, servo_3, 1000);

	conic_execute_motion(device);

	conic_device_close(device);
}

