/*
 * Part of the Conic project - robot arm controller
 *
 * STM32F103 gpio support
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef MCU_STM32F103_GPIO_H
#define MCU_STM32F103_GPIO_H

#include <stdint.h>

#define GPIOA_BASE	0x40010800U /* GPIO Port A */
#define GPIOB_BASE	0x40010C00U /* GPIO Port B */
#define GPIOC_BASE	0x40011000U /* GPIO Port C */
#define GPIOD_BASE	0x40011400U /* GPIO Port D */

struct gpio {
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
};

#define GPIOA	((struct gpio*)GPIOA_BASE)
#define GPIOB	((struct gpio*)GPIOB_BASE)
#define GPIOC	((struct gpio*)GPIOC_BASE)
#define GPIOD	((struct gpio*)GPIOD_BASE)

/* Alternative functions */
void gpio_af(struct gpio *bank, uint8_t pin);

#endif

