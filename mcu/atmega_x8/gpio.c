/*
 * Part of the Conic project - robot arm controller
 *
 * ATMega88/168/328 gpio.
 *
 * I am not a huge fan of redefining stuff from <avr/io.h> but it's probably
 * impossible to get api even close to usable with macro like PORTB / DDRB, eh
 *
 * With something like 'struct gpio' we can pass port and pin directly into
 * driver init function
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

struct gpio *gpio_lookup_by_name(char name)
{
	switch (name) {
		case 'B': return GPIOB;
		case 'C': return GPIOC;
		case 'D': return GPIOD;
	}

	return NULL;
}

