ARCH		:= arm
MARCH		:= cortex-m4

ARM_ROM_START	:= 0x00000000
ARM_RAM_START	:= 0x20000000
ARM_ROM_LENGTH	:= 0x80000
ARM_RAM_LENGTH	:= 0xFF20

ARM_CORE_CLK	:= 64000000

FLASH_CHIP	:= nrf52

this-dir := $(call my-dir)

objects += \
	$(this-dir)irq.o \
	$(this-dir)uart.o \
	$(this-dir)gpio.o \
	$(this-dir)system.o

