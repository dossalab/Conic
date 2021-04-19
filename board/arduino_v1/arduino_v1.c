/*
 * Part of the Conic project - robot arm controller
 *
 * arduino sample board support
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <board/common.h>
#include <mcu/common.h>

void board_init(void)
{
	uart_init(UART_BAUD_115200);
}

