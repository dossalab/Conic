/*
 * Part of the Conic project - robot arm controller
 *
 * STM32F103 (non-connectivity, non-xl-density) interrupts support
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef MCU_STM32F103_IRQ_H
#define MCU_STM32F103_IRQ_H

#define irq_entry_list \
	irq_entry(0,  WWDG_IRG, wwdg_handler) \
	irq_entry(1,  PVD_IRQ, pvd_handler) \
	irq_entry(2,  TAMPER_IRQ, tamper_handler) \
	irq_entry(3,  RTC_IRQ, rtc_handler) \
	irq_entry(4,  FLASH_IRQ, flash_handler) \
	irq_entry(5,  RCC_IRQ, rcc_handler) \
	irq_entry(6,  EXTI0_IRQ, exti0_handler) \
	irq_entry(7,  EXTI1_IRQ, exti1_handler) \
	irq_entry(8,  EXTI2_IRQ, exti2_handler) \
	irq_entry(9,  EXTI3_IRQ, exti3_handler) \
	irq_entry(10, EXTI4_IRQ, exti4_handler) \
	irq_entry(11, DMA1_CHANNEL1, dma1_channel1_handler) \
	irq_entry(12, DMA1_CHANNEL2, dma1_channel2_handler) \
	irq_entry(13, DMA1_CHANNEL3, dma1_channel3_handler) \
	irq_entry(14, DMA1_CHANNEL4, dma1_channel4_handler) \
	irq_entry(15, DMA1_CHANNEL5, dma1_channel5_handler) \
	irq_entry(16, DMA1_CHANNEL6, dma1_channel6_handler) \
	irq_entry(17, DMA1_CHANNEL7, dma1_channel7_handler) \
	irq_entry(18, ADC1_2_IRQ, adc1_2_handler) \
	irq_entry(19, USB_HP_CAN_TX_IRQ, usb_hp_can_tx_handler) \
	irq_entry(20, USB_LP_CAN_RX0_IRQ, usb_lp_can_rx0_handler) \
	irq_entry(21, CAN_RX1_IRQ, can_rx1_handler) \
	irq_entry(22, CAN_SCE_IRQ, can_sce_handler) \
	irq_entry(23, EXTI9_5_IRQ, exti9_5_handler) \
	irq_entry(24, TIM1_BRK_IRQ, tim1_brk_handler) \
	irq_entry(25, TIM1_UP_IRQ, tim1_up_handler) \
	irq_entry(26, TIM1_TRG_COM_IRQ, tim1_trg_com_handler) \
	irq_entry(27, TIM1_CC_IRQ, tim1_cc_handler) \
	irq_entry(28, TIM2_IRQ, tim2_handler) \
	irq_entry(29, TIM3_IRQ, tim3_handler) \
	irq_entry(30, TIM4_IRQ, tim4_handler) \
	irq_entry(31, I2C1_EV_IRQ, i2c1_ev_handler) \
	irq_entry(32, I2C1_ER_IRQ, i2c1_er_handler) \
	irq_entry(33, I2C2_EV_IRQ, i2c2_ev_handler) \
	irq_entry(34, I2C2_ER_IRQ, i2c2_er_handler) \
	irq_entry(35, SPI1_IRQ, spi1_handler) \
	irq_entry(36, SPI2_IRQ, spi2_handler) \
	irq_entry(37, UART1_IRQ, uart1_handler) \
	irq_entry(38, UART2_IRQ, uart2_handler) \
	irq_entry(39, UART3_IRQ, uart3_handler) \
	irq_entry(40, EXTI15_10_IRQ, exti15_10_handler) \
	irq_entry(41, RTCALARM_IRQ, rtcalarm_handler) \
	irq_entry(42, USBWAKEUP_IRQ, usbwakeup_handler)
/*
 * ... For some reason there is more vectors in reference manual, but startup
 * files for medium-density devices declare exactly this amount
 */

#define DECLARE_IRQ_ENUM
#include <arch/arm/declare-irq.h>

#endif

