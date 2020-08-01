ARCH		:= avr

this-dir	:= $(call my-dir)

objects += \
	$(this-dir)uart.o \
	$(this-dir)timer.o \
	$(this-dir)gpio.o

