/*
 * Part of the Conic project - robot arm controller
 *
 * NRF52832 interrupts support
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef MCU_NRF52832_IRQ_H
#define MCU_NRF52832_IRQ_H

#define irq_entry_list \
	irq_entry(0,  POWER_CLOCK_IRQ, power_clock_handler) \
	irq_entry(1,  RADIO_IRQ, radio_handler) \
	irq_entry(2,  UART0_IRQ, uart0_handler) \
	irq_entry(3,  SPI0_TWI0_IRQ, spi0_twi0_handler) \
	irq_entry(4,  SPI1_TWI1_IRQ, spi1_twi1_handler) \
	irq_entry(5,  NFCT_IRQ, nfct_handler) \
	irq_entry(6,  GPIOTE_IRQ, gpiote_handler) \
	irq_entry(7,  SAADC_IRQ, saadc_handler) \
	irq_entry(8,  TIMER0_IRQ, timer0_handler) \
	irq_entry(9,  TIMER1_IRQ, timer1_handler) \
	irq_entry(10, TIMER2_IRQ, timer2_handler) \
	irq_entry(11, RTC0_IRQ, rtc0_handler) \
	irq_entry(12, TEMP_IRQ, temp_handler) \
	irq_entry(13, RNG_IRQ, rng_handler) \
	irq_entry(14, ECB_IRQ, ecb_handler) \
	irq_entry(15, CCM_AAR_IRQ, ccm_aar_handler) \
	irq_entry(16, WDT_IRQ, wdt_handler) \
	irq_entry(17, RTC1_IRQ, rtc1_handler) \
	irq_entry(18, QDEC_IRQ, qdec_handler) \
	irq_entry(19, COMP_LPCOMP_IRQ, comp_lpcomp_handler) \
	irq_entry(20, SWI0_EGU0_IRQ, swi0_egu0_handler) \
	irq_entry(21, SWI1_EGU1_IRQ, swi1_egu1_handler) \
	irq_entry(22, SWI2_EGU2_IRQ, swi2_egu2_handler) \
	irq_entry(23, SWI3_EGU3_IRQ, swi3_egu3_handler) \
	irq_entry(24, SWI4_EGU4_IRQ, swi4_egu4_handler) \
	irq_entry(25, SWI5_EGU5_IRQ, swi5_egu5_handler) \
	irq_entry(26, TIMER3_IRQ, timer3_handler) \
	irq_entry(27, TIMER4_IRQ, timer4_handler) \
	irq_entry(28, PWM0_IRQ, pwm0_handler) \
	irq_entry(29, PDM_IRQ, pdm_handler) \
	irq_entry(32, MWU_IRQ, mwu_handler) /* Yeah, there is a hole here */ \
	irq_entry(33, PWM1_IRQ, pwm1_handler) \
	irq_entry(34, PWM2_IRQ, pwm2_handler) \
	irq_entry(35, SPI2_IRQ, spim2_spis2_spi2_handler) \
	irq_entry(36, RTC2_IRQ, rtc2_handler) \
	irq_entry(37, I2S_IRQ, i2s_handler) \
	irq_entry(38, FPU_IRQ, fpu_handler)

#define DECLARE_IRQ_ENUM
#include <arch/arm/declare-irq.h>

#endif

