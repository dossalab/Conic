/*
 * Part of the Conic project - robot arm controller
 *
 * STM32F103 microsecond resolution timer support.
 * We use TIM2 (General-purpose timer) here
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <mcu/common.h>
#include <misc/stuff.h>
#include <arch/arm/nvic.h>

/*
 * CR1 register bits
 */

/* Direction (0: upcounter, 1: downcounter) */
#define TIM_CR1_DIR_BIT		BIT(4)

/* Counter enable */
#define TIM_CR1_CEN_BIT		BIT(0)

/*
 * DIER (DMA / interrupt enable register) bits
 */

/* Capture/Compare 1 interrupt enable */
#define TIM_DIER_CC1IE_BIT	BIT(1)

/* Update interrupt enable */
#define TIM_DIER_UIE_BIT	BIT(0)

/*
 * SR register bits
 */

/* Capture/Compare 1 interrupt flag */
#define TIM_SR_CC1IF_BIT	BIT(1)

/* Update interrupt flag */
#define TIM_SR_UIF_BIT		BIT(0)

static void (*timer_compare_callback)(void);
static void (*timer_overflow_callback)(void);

/*
 * Timer 2 common interrupt handler
 *
 * STM32 timer is retarded - it sets compare flag even if there was no
 * actual compare (e.g when compare value is higher than overflow value)
 * So we need additional check here...
 */
void tim2_handler(void)
{
	/* Compare interrupt fired */
	if (TIM2->SR & TIM_SR_CC1IF_BIT) {
		if (TIM2->CCR[0] <= TIM2->ARR) {
			timer_compare_callback();
		}

		TIM2->SR &= ~TIM_SR_CC1IF_BIT;
	}

	/* Overflow interrupt fired */
	if (TIM2->SR & TIM_SR_UIF_BIT) {
		timer_overflow_callback();
		TIM2->SR &= ~TIM_SR_UIF_BIT;
	}
}

void timer_on_compare(void (*compare_cb)(void))
{
	if (!compare_cb) {
		/* Disable compare channel 1 interrupts */
		TIM2->DIER &= ~TIM_DIER_CC1IE_BIT;
	} else {
		/* Allow compare channel 1 interrupts */
		TIM2->DIER |= TIM_DIER_CC1IE_BIT;
	}

	timer_compare_callback = compare_cb;
}

void timer_on_overflow(void (*overflow_cb)(void))
{
	if (!overflow_cb) {
		/* Disable overflow ('update') interrupts */
		TIM2->DIER &= ~TIM_DIER_UIE_BIT;
	} else {
		/* Allow overflow ('update') interrupts */
		TIM2->DIER |= TIM_DIER_UIE_BIT;
	}

	timer_overflow_callback = overflow_cb;
}

void timer_set_compare(uint16_t compare)
{
	/* We use channel 1 here, but actual timer contains 4 channels  */
	TIM2->CCR[0] = compare;
}

void timer_set_overflow(uint16_t overflow)
{
	TIM2->ARR = overflow - 1;
}

void timer_start(void)
{
	TIM2->CR1 |= TIM_CR1_CEN_BIT;
}

void timer_stop(void)
{
	TIM2->CR1 &= ~TIM_CR1_CEN_BIT;
}

void timer_init(void)
{
	/* APB1 prescaler is 2, and timer2 multiplier is 2 (See clock map) */
	TIM2->PSC = (ARM_CORE_CLK / 1000000) - 1; /* microsecond tick */
	TIM2->CR1 &= ~TIM_CR1_DIR_BIT;	/* Direction upward */

	/* Individual overflow / compare interrupts will be enabled after */
	nvic_enable_irq(TIM2_IRQ);
}

