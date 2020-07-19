/*
 * Part of the Conic project - robot arm controller
 *
 * NRF52832 UART support
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef MCU_NRF52832_UART_H
#define MCU_NRF52832_UART_H

#include <stdint.h>

/* This magic values are taken from NRF52832 datasheet */
#define UART_BAUD_9600		0x00275000UL /* actual rate: 9598 */
#define UART_BAUD_14400		0x003AF000UL /* actual rate: 14401 */
#define UART_BAUD_19200		0x004EA000UL /* actual rate: 19208 */
#define UART_BAUD_38400		0x009D0000UL /* actual rate: 38369 */
#define UART_BAUD_57600		0x00EB0000UL /* actual rate: 57554 */
#define UART_BAUD_76800		0x013A9000UL /* actual rate: 76923 */
#define UART_BAUD_115200	0x01D60000UL /* actual rate: 115108 */

#define NRF_UARTE0_BASE		0x40002000

struct uart {
	volatile uint32_t TASKS_STARTRX;
	volatile uint32_t TASKS_STOPRX;
	volatile uint32_t TASKS_STARTTX;
	volatile uint32_t TASKS_STOPTX;
	volatile uint32_t __reserved_0[7];
	volatile uint32_t TASKS_FLUSHRX;
	volatile uint32_t __reserved_1[52];
	volatile uint32_t EVENTS_CTS;
	volatile uint32_t EVENTS_NCTS;
	volatile uint32_t EVENTS_RXDRDY;
	volatile uint32_t __reserved_2;
	volatile uint32_t EVENTS_ENDRX;
	volatile uint32_t __reserved_3[2];
	volatile uint32_t EVENTS_TXDRDY;
	volatile uint32_t EVENTS_ENDTX;
	volatile uint32_t EVENTS_ERROR;
	volatile uint32_t __reserved_4[7];
	volatile uint32_t EVENTS_RXTO;
	volatile uint32_t __reserved_5;
	volatile uint32_t EVENTS_RXSTARTED;
	volatile uint32_t EVENTS_TXSTARTED;
	volatile uint32_t __reserved_6;
	volatile uint32_t EVENTS_TXSTOPPED;
	volatile uint32_t __reserved_7[41];
	volatile uint32_t SHORTS;
	volatile uint32_t __reserved_8[63];
	volatile uint32_t INTEN;
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t __reserved_9[93];
	volatile uint32_t ERRORSRC;
	volatile uint32_t __reserved_10[31];
	volatile uint32_t ENABLE;
	volatile uint32_t __reserved_11;

	struct {
		volatile uint32_t RTS;
		volatile uint32_t TXD;
		volatile uint32_t CTS;
		volatile uint32_t RXD;
	} PSEL;

	volatile uint32_t __reserved_12[3];
	volatile uint32_t BAUDRATE;
	volatile uint32_t __reserved_13[3];

	struct {
		volatile uint32_t PTR;
		volatile uint32_t MAXCNT;
		volatile uint32_t AMOUNT;
	} RXD;

	volatile uint32_t __reserved_14;

	struct {
		volatile uint32_t PTR;
		volatile uint32_t MAXCNT;
		volatile uint32_t AMOUNT;
	} TXD;

	volatile uint32_t __reserved_15[7];
	volatile uint32_t CONFIG;
};

#define NRF_UARTE0		((struct uart*)NRF_UARTE0_BASE)

/* UART */
void uart_init(int pin_tx, int pin_rx, int baudrate);

#endif

