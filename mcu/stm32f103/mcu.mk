ARCH		:= arm
MARCH		:= cortex-m3

ARM_ROM_START	:= 0x08000000
ARM_RAM_START	:= 0x20000000
ARM_ROM_LENGTH	:= 64K
ARM_RAM_LENGTH	:= 20K

ARM_CORE_CLK	:= 72000000

FLASH_CHIP	:= stm32f1x
DEBUG_CHIP	:= stm32f1x

this-dir := $(call my-dir)

objects += \
	$(this-dir)rcc.o \
	$(this-dir)gpio.o \
	$(this-dir)uart.o \
	$(this-dir)irq.o \
	$(this-dir)timer.o

