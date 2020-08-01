/*
 * Part of the Conic project - robot arm controller
 *
 * Common MCU hardware-abstraction api
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include MCU_SPECIFIC_HEADER

#ifndef MCU_COMMON_H
#define MCU_COMMON_H

/*
 * UART
 */

void uart_on_receive(void (*receive_cb)(uint8_t byte));

void uart_puts(const char *str);
void uart_send(uint8_t *data, size_t len);
void uart_printf(const char *fmt, ...);

/*
 * GPIO
 */

bool gpio_get(struct gpio *bank, uint8_t pin);
void gpio_set(struct gpio *bank, uint8_t pin);
void gpio_clr(struct gpio *bank, uint8_t pin);
void gpio_toggle(struct gpio *bank, uint8_t pin);

void gpio_in(struct gpio *bank, uint8_t pin);
void gpio_out(struct gpio *bank, uint8_t pin);

/*
 * At least 16 bit microsecond resolution timer
 */

void timer_on_compare(void (*compare_cb)(void));
void timer_on_overflow(void (*overflow_cb)(void));

void timer_set_compare(uint16_t compare);
void timer_set_overflow(uint16_t overflow);

void timer_start(void);
void timer_stop(void);
void timer_init(void);

#endif

