/*
 * Part of the Conic project - robot arm controller
 *
 * ATMega88/168/328 microsecond timer support. Remember, TIMER0
 * is reserved for system tick timer!
 * 
 * Poor little Atmega, 1 microsecond is one overflow every 16 cpu ticks!
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <mcu/common.h>
#include <avr/interrupt.h>
#include <avr/io.h>

/* FIXME: calculate prescalers to let timer work with other frequences */
#if F_CPU != 16000000UL
	#error "this F_CPU is not supported by timer.c. FIXME"
#endif

static void (*timer_callback)(void);

//ISR(TIMER1_COMPA_vect){
//	/* at this point timer_callback should be non-null */
//	timer_callback();
//}
//
//void ustimer_init(void (*timer_cb)(void))
//{
//	timer_callback = timer_cb;
//
//	TCCR1A |= (1 << WGM11); /* Clear timer on compare match (CTC) mode */
//	TCCR1B |= (1 << CS10); /* Prescaler 1 */
//	OCR1A = 15; /* Count from 0 to 15 */
//	TIMSK1 |= (1 << OCIE1A); /* Enable TIMER1 compare interrupt */
//}
//
//void timer_setup_compare(int timer, uint16_t compare, void (*timer_cb)(void))
//{
//
//}
//
////void timer_setup_overflow(int timer, uint16_t compare, void (*timer_cb)(void))
////{
////
////}

void timer_on_compare(void (*compare_cb)(void))
{

}

void timer_on_overflow(void (*overflow_cb)(void))
{

}

void timer_set_compare(uint16_t compare)
{

}

void timer_set_overflow(uint16_t overflow)
{

}

void timer_start(void)
{

}

void timer_stop(void)
{

}

void timer_init(void)
{

}

