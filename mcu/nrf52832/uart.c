/*
 * Part of the Conic project - robot arm controller
 *
 * NRF52832 UART support
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <mcu/common.h>
#include <misc/stuff.h>
#include <arch/arm/nvic.h>
#include <string.h>

/* Write this to ENABLE register to enable UART */
#define NRF_UART_ENABLE		8

/* INTENSET / INTENCLR register bits */
#define INTEN_RXDRDY_BIT	BIT(2)

static void (*uart_receive_callback)(uint8_t byte);
static volatile uint8_t uart_receive_buffer;

void uart0_handler(void)
{
	if (NRF_UARTE0->EVENTS_RXDRDY) {
		NRF_UARTE0->EVENTS_RXDRDY = 0;

		/* Start reception again... */
		NRF_UARTE0->RXD.PTR = (uint32_t)&uart_receive_buffer;
		NRF_UARTE0->RXD.MAXCNT = sizeof(uart_receive_buffer);
		NRF_UARTE0->TASKS_STARTRX = 1;

		uart_receive_callback(uart_receive_buffer);
	}
}

void uart_on_receive(void (*receive_cb)(uint8_t byte))
{
	if (!receive_cb) {
		NRF_UARTE0->RXD.PTR = (uint32_t)NULL;
		NRF_UARTE0->RXD.MAXCNT = 0;

		nvic_disable_irq(UART0_IRQ);
		NRF_UARTE0->INTENCLR = INTEN_RXDRDY_BIT;
		NRF_UARTE0->TASKS_STOPRX = 1;
	} else {
		NRF_UARTE0->RXD.PTR = (uint32_t)&uart_receive_buffer;
		NRF_UARTE0->RXD.MAXCNT = sizeof(uart_receive_buffer);

		nvic_enable_irq(UART0_IRQ);
		NRF_UARTE0->INTENSET = INTEN_RXDRDY_BIT;
		NRF_UARTE0->TASKS_STARTRX = 1;
	}

	uart_receive_callback = receive_cb;
}

void uart_send(uint8_t *data, size_t len)
{
	NRF_UARTE0->TXD.PTR = (uint32_t)data;
	NRF_UARTE0->TXD.MAXCNT = len;

	NRF_UARTE0->TASKS_STARTTX = 1;

	while (NRF_UARTE0->EVENTS_ENDTX == 0);
	NRF_UARTE0->EVENTS_ENDTX = 0;
}

void uart_init(int pin_tx, int pin_rx, int baudrate)
{
	NRF_UARTE0->PSEL.TXD = pin_tx;
	NRF_UARTE0->PSEL.RXD = pin_rx;

	NRF_UARTE0->BAUDRATE = baudrate;
	NRF_UARTE0->ENABLE = NRF_UART_ENABLE;
}

