/*
 * Part of the Conic project - robot arm controller
 *
 * ATMega88/168/328 UART support.
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef MCU_ATMEGA_X8_UART_H
#define MCU_ATMEGA_X8_UART_H

#include <stdint.h>

/*
 * Converts human-readable baudrate into int16 UBRR value
 * TODO: replace this with a more robust formula with proper integer rounding
 */
#define AVR_BAUD(baud)		(((F_CPU / (baud * 16UL))) - 1) 

#define UART_BAUD_9600		AVR_BAUD(9600UL)
#define UART_BAUD_14400		AVR_BAUD(14400UL)
#define UART_BAUD_19200		AVR_BAUD(19200UL)
#define UART_BAUD_38400		AVR_BAUD(38400UL)
#define UART_BAUD_57600		AVR_BAUD(57600UL)
#define UART_BAUD_76800		AVR_BAUD(76800UL)
#define UART_BAUD_115200	AVR_BAUD(115200UL)

void uart_init(uint16_t baud_prescale);

#endif

