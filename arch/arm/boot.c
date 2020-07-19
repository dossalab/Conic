/*
 * Part of the Conic project - robot arm controller
 *
 * ARM cortex-m boot procedure
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <stdint.h>
#include <misc/compiler.h>
#include <arch/common.h>

/* TODO: name this stuff more default way (_etext, _edata, __stack, etc) */
extern uint32_t __stack__;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;
extern uint32_t __data_load__;
extern uint32_t __data_start__;
extern uint32_t __data_end__;

extern void main(void);

void hardfault_handler(void)
{
	while (1) {
		;;
	}
}

void nmi_handler(void)
{
	while (1) {
		;;
	}
}

void svc_handler(void)
{
	while (1) {
		;;
	}
}

void pend_sv_handler(void)
{
	while (1) {
		;;
	}
}

/* __weak means this function can be redefined in other modules */
__weak void systick_handler(void)
{
	while (1) {
		;;
	}
}

void reset_handler(void)
{
	uint32_t *src = &__data_load__;
	uint32_t *dest = &__data_start__;

	while (dest < &__data_end__) *(dest++) = *(src++);

	for (uint32_t *bss = &__bss_start__; bss < &__bss_end__; bss++) {
		*bss = 0x00;
	}

	__disable_irq;
	main();
}

place_section(".isr_vectors") uint32_t isr_table[] = {
	(uint32_t)&__stack__,
	(uint32_t)reset_handler,
	(uint32_t)nmi_handler,
	(uint32_t)hardfault_handler,
	(uint32_t)0,
	(uint32_t)0,
	(uint32_t)0,
	(uint32_t)0,
	(uint32_t)0,
	(uint32_t)0,
	(uint32_t)0,
	(uint32_t)svc_handler,
	(uint32_t)0,
	(uint32_t)0,
	(uint32_t)pend_sv_handler,
	(uint32_t)systick_handler
};

