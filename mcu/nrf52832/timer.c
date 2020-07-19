/*
 * Part of the Conic project - robot arm controller
 *
 * NRF52832 microsecond resolution timer support.
 * We use TIMER0 here. Compare channel 0 is used as actual compare register
 * and overflows are 'emulated' with channel 1
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <mcu/common.h>
#include <misc/stuff.h>
#include <arch/arm/nvic.h>

static void (*timer_compare_callback)(void);
static void (*timer_overflow_callback)(void);

/*
 * Bitmode register values
 */

#define TIMER_BITMODE_16BIT	0
#define TIMER_BITMODE_8BIT	1
#define TIMER_BITMODE_24BIT	2
#define TIMER_BITMODE_32BIT	3

/*
 * Shorts register bits
 */

/* Shortcuts between compare event and clear */
#define TIMER_SHORTS_COMPARE0_CLEAR_BIT		BIT(0)
#define TIMER_SHORTS_COMPARE1_CLEAR_BIT		BIT(1)
#define TIMER_SHORTS_COMPARE2_CLEAR_BIT		BIT(2)
#define TIMER_SHORTS_COMPARE3_CLEAR_BIT		BIT(3)

/*
 * INTENSET / INTENCLR register bits
 */

#define TIMER_INTEN_COMPARE0_BIT		BIT(16)
#define TIMER_INTEN_COMPARE1_BIT		BIT(17)
#define TIMER_INTEN_COMPARE2_BIT		BIT(18)
#define TIMER_INTEN_COMPARE3_BIT		BIT(19)

void timer0_handler(void)
{
	/* Actual compare */
	if (NRF_TIMER0->EVENTS_COMPARE[0]) {
		timer_compare_callback();
		NRF_TIMER0->EVENTS_COMPARE[0] = 0;
	}

	/* Emulated overflow */
	if (NRF_TIMER0->EVENTS_COMPARE[1]) {
		timer_overflow_callback();
		NRF_TIMER0->EVENTS_COMPARE[1] = 0;
	}
}

void timer_on_compare(void (*compare_cb)(void))
{
	if (!compare_cb) {
		/* Disable compare 0 interrupts */
		NRF_TIMER0->INTENCLR = TIMER_INTEN_COMPARE0_BIT;
	} else {
		/* Enable compare 0 interrupts */
		NRF_TIMER0->INTENSET = TIMER_INTEN_COMPARE0_BIT;
	}

	timer_compare_callback = compare_cb;
}

void timer_on_overflow(void (*overflow_cb)(void))
{
	if (!overflow_cb) {
		/* Disable compare 1 interrupts */
		NRF_TIMER0->INTENCLR = TIMER_INTEN_COMPARE1_BIT;
	} else {
		/* Enable compare 1 interrupts */
		NRF_TIMER0->INTENSET = TIMER_INTEN_COMPARE1_BIT;
	}

	timer_overflow_callback = overflow_cb;
}

void timer_set_compare(uint16_t compare)
{
	/* We use channel 1 here, but actual timer contains 4 channels  */
	NRF_TIMER0->CC[0] = compare;
}

void timer_set_overflow(uint16_t overflow)
{
	/* Compare 1 is used for emulating overflow */
	NRF_TIMER0->CC[1] = overflow;
}

void timer_start(void)
{
	NRF_TIMER0->TASKS_START = 1;
}

void timer_stop(void)
{
	NRF_TIMER0->TASKS_STOP = 1;
}

void timer_init(void)
{
	NRF_TIMER0->BITMODE = TIMER_BITMODE_16BIT;

	/* 16 MHz / 2^4 = 1 Mhz (1 us tick) */
	NRF_TIMER0->PRESCALER = 4;

	/* Compare 1 is used for emulating overflow, so clear counter on CC1 */
	NRF_TIMER0->SHORTS |= TIMER_SHORTS_COMPARE1_CLEAR_BIT;

	nvic_enable_irq(TIMER0_IRQ);
}

