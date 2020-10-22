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

void board_led_on(void)
{
	gpio_clr(BOARD_LED_PORT, BOARD_LED_PIN);
}

void board_led_off(void)
{
	gpio_set(BOARD_LED_PORT, BOARD_LED_PIN);
}

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

	/* enable all GPIO clocks */
	rcc_enable_line(RCC_GPIOA);
	rcc_enable_line(RCC_GPIOB);
	rcc_enable_line(RCC_GPIOC);

	/* enable uart */
	board_uart_init();

	/* enable Timer2 clock (TODO: should this be in timer init itself? */
	rcc_enable_line(RCC_TIM2);

	gpio_out(BOARD_LED_PORT, BOARD_LED_PIN);
	board_led_off(); /* LED is active low on this board */
}

