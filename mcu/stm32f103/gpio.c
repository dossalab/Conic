/*
 * Part of the Conic project - robot arm controller
 *
 * STM32F103 gpio support
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <mcu/common.h>

bool gpio_get(struct gpio *bank, int pin)
{
	return !!(bank->IDR & (1 << pin));
}

void gpio_set(struct gpio *bank, int pin)
{
	bank->ODR |= (1 << pin);
}

void gpio_clr(struct gpio *bank, int pin)
{
	bank->ODR &= ~(1 << pin);
}

void gpio_toggle(struct gpio *bank, int pin)
{
	bank->ODR ^= (1 << pin);
}

void gpio_in(struct gpio *bank, int pin)
{
	if (pin < 8) {
		bank->CRL &= ~(0b1111 << 4 * pin);
		bank->CRL |=  (0b0100 << 4 * pin);
	} else {
		bank->CRH &= ~(0b1111 << 4 * (pin - 8));
		bank->CRH |=  (0b0100 << 4 * (pin - 8));
	}
}

void gpio_out(struct gpio *bank, int pin)
{
	if (pin < 8) {
		bank->CRL &= ~(0b1111 << 4 * pin);
		bank->CRL |=  (0b0011 << 4 * pin);
	} else {
		bank->CRH &= ~(0b1111 << 4 * (pin - 8));
		bank->CRH |=  (0b0011 << 4 * (pin - 8));
	}
}

/*
 * TODO: replace this with something like gpio_config with more parameters
 * like pullup, speed, etc...
 */
void gpio_af(struct gpio *bank, int pin)
{
	if (pin < 8) {
		bank->CRL &= ~(0b1100 << 4 * pin);
		bank->CRL |=  (0b1000 << 4 * pin);
	} else {
		bank->CRH &= ~(0b1100 << 4 * (pin - 8));
		bank->CRH |=  (0b1000 << 4 * (pin - 8));
	}
}

