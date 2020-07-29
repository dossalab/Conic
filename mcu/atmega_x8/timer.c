/*
 * Part of the Conic project - robot arm controller
 *
 * ATMega88/168/328 microsecond timer support. Remember, TIMER0
 * is reserved for system tick timer!
 *
 * We use TIMER1 here. Compare channel B (OCR1B) is used as actual compare
 * register and overflows are 'emulated' with channel A (OCR1A)
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <arch/common.h>
#include <mcu/common.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/*
 * AVR timers are stupid. Available dividers are 1, 8, 64, 256 and 1024,
 * and it's impossible to clearly get 1 microsecond tick on stock
 * 16 Mhz Arduino without dividing compare channel values
 */

#define TIMER_PRESCALER_1	((0 << CS12) | (0 << CS11) | (1 << CS10))
#define TIMER_PRESCALER_8	((0 << CS12) | (1 << CS11) | (0 << CS10))
#define TIMER_PRESCALER_64	((0 << CS12) | (1 << CS11) | (1 << CS10))
#define TIMER_PRESCALER_256	((1 << CS12) | (0 << CS11) | (0 << CS10))
#define TIMER_PRESCALER_1024	((1 << CS12) | (0 << CS11) | (1 << CS10))
#define TIMER_PRESCALER_MASK	((1 << CS12) | (1 << CS11) | (1 << CS10))

/* Arduino UNO / Mega clocked from external crystal */
#if F_CPU == 16000000UL
	#define OCR_DIVIDER		4
	#define TIMER_PRESCALER		TIMER_PRESCALER_64

/* AVR clocked from internal 8 Mhz RC oscillator, or Arduino pro mini */
#elif F_CPU == 8000000UL
	#define OCR_DIVIDER		1
	#define TIMER_PRESCALER		TIMER_PRESCALER_8

/* AVR clocked from internal 8 Mhz RC oscillator divided by 8 */
#elif F_CPU == 1000000UL
	#define OCR_DIVIDER		1
	#define TIMER_PRESCALER		TIMER_PRESCALER_1

#else
	#error "this F_CPU is not supported by timer.c. FIXME"
#endif

static void (*timer_compare_callback)(void);
static void (*timer_overflow_callback)(void);

/* Timer clears on compare A. This is our overflow */
ISR(TIMER1_COMPA_vect)
{
	timer_overflow_callback();
}

ISR(TIMER1_COMPB_vect)
{
	timer_compare_callback();
}

void timer_on_compare(void (*compare_cb)(void))
{
	if (!compare_cb) {
		/* Disable TIMER1 compare B interrupt */
		TIMSK1 &= ~(1 << OCIE1B);
	} else {
		/* Enable TIMER1 compare B interrupt */
		TIMSK1 |= (1 << OCIE1B);
	}

	timer_compare_callback = compare_cb;
}

void timer_on_overflow(void (*overflow_cb)(void))
{
	/* Overflows are 'emulated' via compare channel A */
	if (!overflow_cb) {
		/* Disable TIMER1 compare A interrupt */
		TIMSK1 &= ~(1 << OCIE1A);
	} else {
		/* Enable TIMER1 compare A interrupt */
		TIMSK1 |= (1 << OCIE1A);
	}

	timer_overflow_callback = overflow_cb;
}

/* XXX: do we really need atomic access here? */
void timer_set_compare(uint16_t compare)
{
	volatile uint16_t ocr_value;

	ocr_value = compare / OCR_DIVIDER;

	__disable_irq;
	OCR1B = ocr_value;
	__enable_irq;
}

void timer_set_overflow(uint16_t overflow)
{
	volatile uint16_t ocr_value;

	ocr_value = overflow / OCR_DIVIDER;

	__disable_irq;
	OCR1A = ocr_value;
	__enable_irq;
}

void timer_start(void)
{
	TCCR1B |= TIMER_PRESCALER;
}

void timer_stop(void)
{
	/* No prescaler - timer stopped */
	TCCR1B &= ~TIMER_PRESCALER_MASK;
}

void timer_init(void)
{
	/* Clear timer on OCR1A compare match (CTC) */
	TCCR1A = (1 << WGM11);
	TCCR1B = 0;
}

