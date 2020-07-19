/*
 * Part of the Conic project - robot arm controller
 *
 * Arm motion controller. 5 servos arm, and claw
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <core/arm.h>
#include <board/common.h>
#include <drivers/servo.h>
#include <misc/stuff.h>

DECLARE_SERVO(servo_1, BOARD_SERVO_1_PORT, BOARD_SERVO_1_PIN);
DECLARE_SERVO(servo_2, BOARD_SERVO_1_PORT, BOARD_SERVO_1_PIN);
DECLARE_SERVO(servo_3, BOARD_SERVO_1_PORT, BOARD_SERVO_1_PIN);

static struct servo *servo_array[] = { &servo_1, &servo_2, &servo_3 };

//enum units {
//	UNITS_MM, UNITS_INCH, UNITS_RAW
//};
//
//struct machine_axis {
//	struct gpio_bank *gpio;
//	int step_pin, dir_pin;
//	int br_error, br_steps, br_counter;
//	bool done;
//};
//
//static struct machine_axis axes[] = {
//	{ .gpio = GPIO_P0, .step_pin = 1, .dir_pin = 2 },
//	{ .gpio = GPIO_P0, .step_pin = 3, .dir_pin = 4 },
//	{ .gpio = GPIO_P0, .step_pin = 5, .dir_pin = 6 },
//	{ .gpio = GPIO_P0, .step_pin = 7, .dir_pin = 8 }
//};
//#define AXIS_COUNT	ARRAY_LEN(axes)
//
//static enum units current_units = UNITS_MM;
//static bool rising_edge = true;
//
//int steppers_units2steps(float units)
//{
//	int result;
//
//	switch (current_units) {
//	case UNITS_MM:
//		result = units * CONFIG_STEPS_PER_MM;
//		break;
//	case UNITS_INCH:
//		result = units * CONFIG_STEPS_PER_MM * MM_TO_INCH;
//		break;
//	case UNITS_RAW:
//		result = units;
//		break;
//	default:
//		panic("Internal error: unable to determine current_units");
//	}
//
//	return result;
//}
//
//int steppers_move(float amount[], int count)
//{
//	struct machine_axis *axis;
//
//	if (count > AXIS_COUNT) {
//		return -1;
//	}
//
//	for (int i = 0; i < count; i++) {
//		axis = &axes[i];
//		axis->br_steps = steppers_units2steps(amount[i]);
//		axis->done = false;
//	}
//
//	return 0;
//}
//
//void steppers_update(void)
//{
//	struct machine_axis *axis;
//
//	for (int i = 0; i < AXIS_COUNT; i++) {
//		axis = &axes[i];
//
//		if (rising_edge) {
//			axis->br_error += axis->br_steps;
//
//			if (2 * axis->br_error >= axis->br_steps) {
//				gpio_set(axis->gpio, axis->step_pin);
//
//				axis->br_counter++;    
//				axis->br_error -= axis->br_steps;
//			}
//		} else {
//			gpio_clr(axis->gpio, axis->step_pin);
//
//			if (axis->br_counter >= axis->br_steps) {
//				axis->done = true;
//			}
//		}
//	} 
//
//	rising_edge = !rising_edge;
//}

bool arm_move(float x, float y, float z, float a)
{
	return false;
}

void arm_init(void)
{
	servo_init(servo_array, ARRAY_LEN(servo_array));
}

