/*
 * Part of the Conic project - robot arm controller
 *
 * Common MCU hardware-abstraction api
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <mcu/common.h>

void uart_puts(const char *msg)
{
	uart_send((uint8_t *)msg, strlen(msg));
}

void uart_printf(const char *fmt, ...)
{
	va_list arg;
	char buf[64];

	va_start(arg, fmt);
	vsnprintf(buf, sizeof(buf), fmt, arg);
	va_end(arg);

	uart_puts(buf);
}

