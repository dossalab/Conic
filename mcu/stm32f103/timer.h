/*
 * Part of the Conic project - robot arm controller
 *
 * STM32F103 microsecond resolution timer support.
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef MCU_STM32F103_TIMER_H
#define MCU_STM32F103_TIMER_H

struct timer {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t __reserved;
	volatile uint32_t CCR[4];
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
};

#define TIM2_BASE	0x40000000U
#define TIM3_BASE	0x40000400U
#define TIM4_BASE	0x40000800U
#define TIM5_BASE	0x40000C00U

#define TIM2		((struct timer *)TIM2_BASE)
#define TIM3		((struct timer *)TIM3_BASE)
#define TIM4		((struct timer *)TIM4_BASE)
#define TIM5		((struct timer *)TIM5_BASE)

#endif

