MCU		:= atmega_x8
AVR_MMCU	:= atmega328
AVR_FCPU	:= 16000000

FLASH_CHIP	:= atmega328p
FLASH_ADAPTER	:= arduino

objects	+= $(call my-dir)arduino_v1.o

