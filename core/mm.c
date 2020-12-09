/*
 * Part of the Conic project - robot arm controller
 *
 * Motion / servo manager.
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <core/mm.h>

static struct servo *lookup_by_handle(int8_t handle)
{
	return NULL;
}

int8_t mm_create_servo(struct gpio *port, int8_t pin)
{
	return 0;
}

int8_t mm_move_servo(int8_t handle, uint16_t pulse)
{
	return 0;
}

int8_t mm_execute_motion(void)
{
	return 0;
}

void mm_system_init(void)
{

}

