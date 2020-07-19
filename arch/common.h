/*
 * Part of the Conic project - robot arm controller
 *
 * Common ARCH api
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

/*
 * Arch-related stuff mostly will be defined as macro....
 * We don't have any way to force specific set of macro to be implemented in
 * ARCH_SPECIFIC_HEADER... At least it must define:
 * __disable_irq, __enable_irq - disable / enable interrupts locally
 * arch_flag_t - some sort of atomic flag, like char for AVR / int for ARM
 */

/* Setup 1 ms resolution timer for task manager */
void arch_timer_init(void (*timer_handler)(void));

#include ARCH_SPECIFIC_HEADER

