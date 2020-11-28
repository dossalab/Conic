/*
 * Part of the Conic project - robot arm controller
 *
 * AVR system tick timer. We use TIMER0 here
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <avr/io.h>
#include <avr/interrupt.h>

static void (*arch_timer_handler)(void);

/* FIXME: calculate prescalers to let timer work with other frequences */
#if F_CPU != 16000000UL
	#error "this F_CPU is not supported by timer.c. FIXME"
#endif

ISR(TIMER0_OVF_vect){
	/* arch_timer_handler should be not null at this point... */
	arch_timer_handler();
}

/*
 * There is a bit of error here because 16000000 / 64 / 256 is a bit less
 * than 1000 ticks per second... FIXME
 */
void arch_timer_init(void (*timer_handler)(void))
{
	arch_timer_handler = timer_handler;

	TCCR0B |= (1 << CS01) | (1 << CS00); /* prescaler 64 */

#ifdef AVR_COMMON_TIMSK
	TIMSK |= (1 << TOIE0);
#else
	TIMSK0 |= (1 << TOIE0); /* Enable TIMER0 overflow interrupt */
#endif
}

