/*
 * Part of the Conic project - robot arm controller
 *
 * ARM cortex-m SysTick
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <arch/arm/nvic.h>
#include <arch/arm/systick.h>
#include <misc/stuff.h>

/* SysTick bits */
#define SYSTICK_CTRL_ENABLE_BIT		BIT(0)
#define SYSTICK_CTRL_TICKINT_BIT	BIT(1)
#define SYSTICK_CTRL_CLKSOURCE_BIT	BIT(2)

static void (*arch_timer_handler)(void);

void systick_handler(void)
{
	/* arch_timer_handler should be not null at this point... */
	arch_timer_handler();
}

static void systick_init(uint32_t ticks)
{
	SYSTICK->LOAD = ticks - 1;
	SYSTICK->VAL  = 0UL;
	SYSTICK->CTRL = SYSTICK_CTRL_CLKSOURCE_BIT
			| SYSTICK_CTRL_TICKINT_BIT
			| SYSTICK_CTRL_ENABLE_BIT;
}

void arch_timer_init(void (*timer_handler)(void))
{
	arch_timer_handler = timer_handler;
	systick_init(ARM_CORE_CLK / 1000);
}

