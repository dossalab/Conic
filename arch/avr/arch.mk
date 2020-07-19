# We use allow-override here because CC and LD are set
# by make itself, so simpler ?= approach won't work

$(call allow-override,CC,avr-gcc)
$(call allow-override,LD,avr-gcc)
$(call allow-override,SIZE,avr-size)

$(call check-defined, AVR_MMCU, MCU only means series for AVR because lots \
	of chips share same peripheral drivers (like atmega88/168/328))

$(call check-defined, AVR_FCPU, F_CPU is needed for UART, timers, etc...)

LDFLAGS	+= \
	-mmcu=$(AVR_MMCU)

CFLAGS += \
	-mmcu=$(AVR_MMCU) \
	-DF_CPU=$(AVR_FCPU) \
	-DARCH_LITTLE_ENDIAN

objects += \
	$(call my-dir)timer.o
