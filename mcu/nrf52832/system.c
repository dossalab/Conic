/*
 * Part of the Conic project - robot arm controller
 *
 * NRF52832 common system functions
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <mcu/common.h>

int system_temperature(void)
{
	NRF_TEMP->TASKS_START = 1;
	while (NRF_TEMP->EVENTS_DATARDY == 0);
	NRF_TEMP->EVENTS_DATARDY = 0;

	return (int)NRF_TEMP->TEMP / 4;
}

void system_ext_crystal_on(void)
{
	NRF_CLOCK->TASKS_HFCLKSTART = 1;

	/* TODO: implement timeout here */
	while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0) {
		;;
	}
}

