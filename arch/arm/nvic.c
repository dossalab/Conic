/*
 * Part of the Conic project - robot arm controller
 *
 * ARM Cortex-M3/M4 interrupt controller (NVIC).
 *
 * Seems like main difference between generations is in vector count, so
 * this stuff should also work on Cortex-M0, for example...
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <arch/arm/nvic.h>

void nvic_enable_irq(uint32_t irq)
{
	NVIC->ISER[irq >> 5] = (1UL << (irq & 0x1FUL));
}

void nvic_disable_irq(uint32_t irq)
{
	NVIC->ICER[irq >> 5] = (1UL << (irq & 0x1FUL));
}

