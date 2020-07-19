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

#ifndef ARCH_ARM_NVIC_H
#define ARCH_ARM_NVIC_H

#include <stdint.h>

struct nvic {
	volatile uint32_t ISER[8];
	volatile uint32_t __reserved_0[24];
	volatile uint32_t ICER[8];
	volatile uint32_t __reserved_1[24];
	volatile uint32_t ISPR[8];
	volatile uint32_t __reserved_2[24];
	volatile uint32_t ICPR[8];
	volatile uint32_t __reserved_3[24];
	volatile uint32_t IABR[8];
	volatile uint32_t __reserved_4[56];
	volatile uint8_t IP[240];
        volatile uint32_t __reserved_5[644U];
	volatile uint32_t STIR;
};

#define NVIC_BASE	0xE000E100UL
#define NVIC		((struct nvic *)NVIC_BASE)

void nvic_enable_irq(uint32_t irq);
void nvic_disable_irq(uint32_t irq);

#endif

