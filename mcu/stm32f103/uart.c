/*
 * Part of the Conic project - robot arm controller
 *
 * STM32F103 UART support.
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <mcu/common.h>
#include <arch/arm/nvic.h>
#include <misc/stuff.h>

/*
 * Status register bits
 */

/* Transmit data register empty (0: register empty, 1: data is transferred) */
#define UART_SR_TXE_BIT		BIT(7)

/* Read data register not empty (0: register empty, 1: data is received) */
#define UART_SR_RXNE_BIT	BIT(5)

/*
 * CR1 register bits
 */

/* UART receiver enable (0: disabled, 1: enabled) */
#define UART_CR1_RE_BIT		BIT(2)

/* UART transmitter enable (0: disabled, 1: enabled) */
#define UART_CR1_TE_BIT		BIT(3)

/* UART receiver RXNE interrupt enable (0: disabled, 1: enabled) */
#define UART_CR1_RXNEIE_BIT	BIT(5)

/* UART enable (0: disabled, 1: enabled) */
#define UART_CR1_UE_BIT		BIT(13)

static void (*uart_receive_callback)(uint8_t byte);

void uart1_handler(void)
{
	volatile uint8_t byte;

	/* Flags will clear automatically after read from DR */
	byte = UART1->DR;

	uart_receive_callback(byte);
}

void uart_on_receive(void (*receive_cb)(uint8_t byte))
{
	if (!receive_cb) {
		UART1->CR1 &= ~UART_CR1_RXNEIE_BIT;
		nvic_disable_irq(UART1_IRQ);
	} else {
		UART1->CR1 |= UART_CR1_RXNEIE_BIT;
		nvic_enable_irq(UART1_IRQ);
	}

	uart_receive_callback = receive_cb;
}

void uart_send(uint8_t *data, size_t len)
{
	for (size_t i = 0; i < len; i++) {
		while ((UART1->SR & UART_SR_TXE_BIT) == 0) {
			;;
		}

		UART1->DR = data[i];
	}
}

void uart_init(uint16_t baud_prescale)
{
	UART1->BRR = baud_prescale;

	/* Enable UART transmitter and receiver */
	UART1->CR1 |= UART_CR1_TE_BIT | UART_CR1_RE_BIT;

	/* Enable UART */
	UART1->CR1 |= UART_CR1_UE_BIT;
}

