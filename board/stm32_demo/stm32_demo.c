/*
 * Part of the Conic project - robot arm controller
 *
 * STM32 demo board support
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <board/common.h>
#include <mcu/common.h>

static inline void board_uart_init(void)
{
	rcc_enable_line(RCC_UART1);

	/* You can remap this pins, actually... */
	gpio_out(GPIOA, 9);
	gpio_in(GPIOA, 10);

	gpio_set(GPIOA, 10); /* Enable pull-up on RX pin */
	gpio_af(GPIOA, 9);
	//gpio_af(GPIOA, 10);

	uart_init(UART_BAUD_115200);
}

void board_init(void)
{
	rcc_setup_clocks();

	/* enable alternative function clock */
	rcc_enable_line(RCC_AFIO);

	/* enable GPIO clocks */
	rcc_enable_line(RCC_GPIOA);

	/* enable uart */
	board_uart_init();

	/* enable Timer2 clock (TODO: should this be in timer init itself? */
	rcc_enable_line(RCC_TIM2);
}

