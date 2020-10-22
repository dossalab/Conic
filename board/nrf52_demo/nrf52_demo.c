/*
 * Part of the Conic project - robot arm controller
 *
 * NRF52 demo board support
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <board/common.h>
#include <mcu/common.h>

void board_led_on(void)
{
	gpio_set(BOARD_LED_PORT, BOARD_LED_PIN);
}

void board_led_off(void)
{
	gpio_clr(BOARD_LED_PORT, BOARD_LED_PIN);
}

void board_init(void)
{
	system_ext_crystal_on();

	gpio_out(BOARD_LED_PORT, BOARD_LED_PIN);
	uart_init(BOARD_UART_TX_PIN, BOARD_UART_RX_PIN, UART_BAUD_115200);
}

