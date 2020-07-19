/*
 * Part of the Conic project - robot arm controller
 *
 * ATMega88/168/328 UART.
 * This chips equipped with a single uart on pins PD1 -> TXD, PD0 -> RXD
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <mcu/common.h>

static void (*uart_receive_callback)(uint8_t byte);

ISR(USART_RX_vect)
{
	volatile uint8_t byte;

	byte = UDR0;

	/* at this point uart_receive_callback should be non-null */
	uart_receive_callback(byte);
}

void uart_on_receive(void (*receive_cb)(uint8_t byte))
{
	if (!receive_cb) {
		/* disable reception */
		UCSR0B &= ~((1 << RXCIE0) | (1 << RXEN0));
	} else {
		/* allow reception */
		UCSR0B |= (1 << RXCIE0) | (1 << RXEN0);
	}

	uart_receive_callback = receive_cb;
}

void uart_send(uint8_t *data, size_t len)
{
	for (size_t i = 0; i < len; i++) {
		while ((UCSR0A & (1 << UDRE0)) == 0) {
			;;
		}

		UDR0 = data[i];
	}
}

void uart_init(uint16_t baud_prescale)
{
	UCSR0B |= (1 << TXEN0);
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);

	UBRR0H = (baud_prescale >> 8);
	UBRR0L = baud_prescale;
}

