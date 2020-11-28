/*
 * Part of the Conic project - robot arm controller
 *
 * ATtiny2313/4313 GPIO.
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <mcu/common.h>

bool gpio_get(struct gpio *bank, uint8_t pin)
{
	return !!(bank->PIN & (1 << pin));
}

void gpio_set(struct gpio *bank, uint8_t pin)
{
	bank->PORT |= (1 << pin);
}

void gpio_clr(struct gpio *bank, uint8_t pin)
{
	bank->PORT &= ~(1 << pin);
}

void gpio_toggle(struct gpio *bank, uint8_t pin)
{
	bank->PORT ^= (1 << pin);
}

void gpio_in(struct gpio *bank, uint8_t pin)
{
	bank->DDR &= ~(1 << pin);
}

void gpio_out(struct gpio *bank, uint8_t pin)
{
	bank->DDR |= (1 << pin);
}

