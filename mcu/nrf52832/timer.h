/*
 * Part of the Conic project - robot arm controller
 *
 * NRF52832 microsecond resolution timer support.
 * We use TIMER0 here.
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef MCU_NRF52832_TIMER_H
#define MCU_NRF52832_TIMER_H

struct timer {
	volatile uint32_t TASKS_START;
	volatile uint32_t TASKS_STOP;
	volatile uint32_t TASKS_COUNT;
	volatile uint32_t TASKS_CLEAR;
	volatile uint32_t TASKS_SHUTDOWN;	/* deprecated! */
	volatile uint32_t __reserved_0[11];
	volatile uint32_t TASKS_CAPTURE[6];
	volatile uint32_t __reserved_1[58];
	volatile uint32_t EVENTS_COMPARE[6];
	volatile uint32_t __reserved_2[42];
	volatile uint32_t SHORTS;
	volatile uint32_t __reserved_3[64];
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t __reserved_4[126];
	volatile uint32_t MODE;
	volatile uint32_t BITMODE;
	volatile uint32_t __reserved_5;
	volatile uint32_t PRESCALER;
	volatile uint32_t __reserved_6[11];
	volatile uint32_t CC[6];	/* Only 4 available on Timer 0,1,2 */
};

#define NRF_TIMER0_BASE		0x40008000UL
#define NRF_TIMER1_BASE		0x40009000UL
#define NRF_TIMER2_BASE		0x4000A000UL
#define NRF_TIMER3_BASE		0x4001A000UL
#define NRF_TIMER4_BASE		0x4001B000UL

#define NRF_TIMER0		((struct timer *)NRF_TIMER0_BASE)
#define NRF_TIMER1		((struct timer *)NRF_TIMER1_BASE)
#define NRF_TIMER2		((struct timer *)NRF_TIMER2_BASE)
#define NRF_TIMER3		((struct timer *)NRF_TIMER3_BASE)
#define NRF_TIMER4		((struct timer *)NRF_TIMER4_BASE)

#endif

