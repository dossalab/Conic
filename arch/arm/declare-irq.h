/*
 * Part of the Conic project - robot arm controller
 *
 * ARM cortex-m interrupt support.
 *
 * Interrupt support is based on X-macro. MCU header will define irq_entry_list
 * of macro irq_entry like this:
 *
 * #define irq_entry_list \
 *     irq_entry(<irq number>, <irq name>, <irq handler>) \
 *     ...
 *
 * declare DECLARE_IRQ_ENUM in header or DECLARE_IRQ_VECTORS in module file
 * and then include this header.
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

/* We do not need header guard here... */

#include <misc/compiler.h>	/* for __weak and place_section */
#include <stdint.h>

#ifndef irq_entry_list
	#error "irq_entry_list is not defined"
#endif

#if defined(DECLARE_IRQ_ENUM)
	#define irq_entry(nvic_no, nvic_name, handler_name) \
		nvic_name = nvic_no,

	enum {
		irq_entry_list
	};

	#undef irq_entry
	#undef DECLARE_IRQ_ENUM

#elif defined(DECLARE_IRQ_VECTORS)
	/* Spawn empty IRQ handlers */
	#define irq_entry(nvic_no, nvic_name, handler_name) \
		__weak void handler_name(void) { \
			while (1) { \
				;; \
			} \
		} \

	irq_entry_list
	#undef irq_entry

	/* define interrupt vector table */
	#define irq_entry(nvic_no, nvic_name, handler_name) \
		[nvic_name] = (uint32_t)handler_name,

	place_section(".mcu_isr_vectors") uint32_t mcu_isr_table[] = {
		irq_entry_list
	};

	#undef irq_entry
	#undef DECLARE_IRQ_VECTORS
#else
	#error "Declare DECLARE_IRQ_VECTORS or DECLARE_IRQ_ENUM!"
#endif

