/*
 * Part of the Conic project - robot arm controller
 *
 * STM32F103 UART support.
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef MCU_STM32F103_UART_H
#define MCU_STM32F103_UART_H

#include <stdint.h>

/* UART1 is clocked from APB2 which is fixed to ARM_CORE_CLK in our case */
#define STM32_UART_CLOCK(baud)		(ARM_CORE_CLOCK / (baud))

#define UART_BAUD_9600		STM32_UART_CLOCK(9600)
#define UART_BAUD_14400		STM32_UART_CLOCK(14400)
#define UART_BAUD_19200		STM32_UART_CLOCK(19200)
#define UART_BAUD_38400		STM32_UART_CLOCK(38400)
#define UART_BAUD_57600		STM32_UART_CLOCK(57600)
#define UART_BAUD_76800		STM32_UART_CLOCK(76800)
#define UART_BAUD_115200	STM32_UART_CLOCK(115200)

#define UART1_BASE	0x40013800

struct uart {
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
};

#define UART1		((struct uart *)UART1_BASE)

void uart_init(uint16_t baud_prescale);

#endif

