/*
 * Part of the Conic project - robot arm controller
 *
 * NRF52832 gpio support
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <mcu/common.h>

bool gpio_get(struct gpio *bank, uint8_t pin)
{
	return !!(bank->IN & (1 << pin));
}

void gpio_set(struct gpio *bank, uint8_t pin)
{
	bank->OUT |= (1 << pin);
}

void gpio_clr(struct gpio *bank, uint8_t pin)
{
	bank->OUT &= ~(1 << pin);
}

void gpio_toggle(struct gpio *bank, uint8_t pin)
{
	bank->OUT ^= (1 << pin);
}

void gpio_in(struct gpio *bank, uint8_t pin)
{
	/* Connect input buffer */
	bank->PIN_CNF[pin] &= ~(1 << 1);

	bank->DIR &= ~(1 << pin);
}

void gpio_out(struct gpio *bank, uint8_t pin)
{
	/* Disconnect input buffer */
	bank->PIN_CNF[pin] |= (1 << 1);

	bank->DIR |= (1 << pin);
}

