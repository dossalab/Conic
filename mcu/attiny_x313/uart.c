/*
 * Part of the Conic project - robot arm controller
 *
 * ATtiny2313/4313 UART.
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

	byte = UDR;

	/* at this point uart_receive_callback should be non-null */
	uart_receive_callback(byte);
}

void uart_on_receive(void (*receive_cb)(uint8_t byte))
{
	if (!receive_cb) {
		/* disable reception */
		UCSRB &= ~((1 << RXCIE) | (1 << RXEN));
	} else {
		/* allow reception */
		UCSRB |= (1 << RXCIE) | (1 << RXEN);
	}

	uart_receive_callback = receive_cb;
}

void uart_send(uint8_t *data, size_t len)
{
	for (size_t i = 0; i < len; i++) {
		while ((UCSRA & (1 << UDRE)) == 0) {
			;;
		}

		UDR = data[i];
	}
}

void uart_init(uint16_t baud_prescale)
{
	UCSRB |= (1 << TXEN);
	UCSRC |= (1 << UCSZ0) | (1 << UCSZ1);

	UBRRH = (baud_prescale >> 8);
	UBRRL = baud_prescale;
}

