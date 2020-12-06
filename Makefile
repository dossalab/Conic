#
# Part of the Conic project - robot arm controller
#
# See LICENSE.md for licensing information
# Roman Luitko, 2020
#

include scripts/build.mk

ECHO	:= printf "[%s]\t%s\n"

# We support cross-compilation for host targets, useful for windows build
PREFIX	?= /usr/local
HOSTCC	:= $(CROSS_COMPILE)gcc
HOSTLD	:= $(CROSS_COMPILE)gcc

elf	:= conic.elf
lib	:= host/libconic$(call obtain-shared-extension, $(HOSTCC))

objects	:= \
	core/serial.o \
	core/main.o \
	mcu/common.o \
	misc/crc7.o \
	drivers/servo.o

# compile both windows and linux objects - there are appropriate checks inside
host-objects := \
	host/libconic.o \
	host/serial_windows.o \
	host/serial_unix.o

# FIXME: is -Wno-discarded-qualifiers really a good idea?
CFLAGS	:= \
	-std=gnu99 \
	-Wall \
	-Wshadow \
	-Wno-main \
	-Wno-discarded-qualifiers \
	-I. -g3 -Og \
	-fdata-sections -ffunction-sections

LDFLAGS	:= -lm -Wl,--gc-sections

HOSTCFLAGS := \
	-fPIC \
	-Wno-format-truncation \
	-I. \
	-Wall

HOSTLDFLAGS := \
	-shared

# check target, we want BOARD variable to be set for firmware builds
ifneq ($(filter all firmware size flash debug, $(call get-make-targets)),)
    $(call check-defined, BOARD, See 'board' directory for available boards)

    include board/$(BOARD)/board.mk
    $(call check-defined, MCU, Probably you have selected unsupported board!)

    include mcu/$(MCU)/mcu.mk
    $(call check-defined, ARCH)

    include arch/$(ARCH)/arch.mk

    # MCU_SPECIFIC_HEADER contains mcu-specific stuff
    # Usually inits are hardware-specific, peripheral api is common
    CFLAGS += -DMCU_SPECIFIC_HEADER="<mcu/$(MCU)/mcu.h>"

    # Board-specific header will contain definitions that rest of the program
    # can use (where is leds, where are buttons, etc...)
    CFLAGS += -DBOARD_SPECIFIC_HEADER="<board/$(BOARD)/board.h>"

    # ARCH-specific header will contain at least way to disable/enable interrupts
    # to implement some sort of locking
    CFLAGS += -DARCH_SPECIFIC_HEADER="<arch/$(ARCH)/arch.h>"

    # Export ARCH, MCU, BOARD to C preprocessor just in case...
    CFLAGS += -DARCH_$(ARCH) -DMCU_$(MCU) -DBOARD_$(BOARD)
endif

all: firmware library

# Firmware target (cross-compilation)
firmware: $(elf) size

%.o : %.c
	@ $(ECHO) CC "$@"
	@ $(CC) $(CFLAGS) -c $< -o $@

$(elf) : $(objects)
	@ $(ECHO) LD "$@"
	@ $(LD) $^ $(LDFLAGS) -o $@

size:
	@ $(SIZE) $(elf)

flash: $(elf)
	$(call check-defined, FLASH_CHIP)
	$(call check-defined, FLASH_ADAPTER)

	@ $(ECHO) FLASH "$^"
	@ scripts/flash.sh $(FLASH_CHIP) $(FLASH_ADAPTER) $<

debug: $(elf)
	$(call check-defined, GDB, only gdb + openocd is supported)
	$(call check-defined, DEBUG_CHIP, is debug supported on your chip?)
	$(call check-defined, DEBUG_ADAPTER)

	@ $(ECHO) DEBUG "$^"
	@ scripts/debug.sh $(GDB) $(DEBUG_CHIP) $(DEBUG_ADAPTER) $<

shell: $(lib)
	@ $(ECHO) SHELL "$^"
	@ host/shell.py

# Host target (non cross-compilation, shared)
library: $(lib)

host/%.o : host/%.c
	@ $(ECHO) HSTCC "$@"
	@ $(HOSTCC) $(HOSTCFLAGS) -c $< -o $@

$(lib) : $(host-objects)
	@ $(ECHO) HSTLD "$@"
	@ $(HOSTLD) $^ $(HOSTLDFLAGS) -o $@

install: $(lib)
	install -m 644 $(lib) $(PREFIX)/lib
	install -m 644 host/libconic.h  $(PREFIX)/include
	install -m 644 host/libconic.pc $(PREFIX)/lib/pkgconfig
	ldconfig

uninstall:
	$(RM) $(PREFIX)/lib/$(notdir $(lib))
	$(RM) $(PREFIX)/include/libconic.h
	$(RM) $(PREFIX)/lib/pkgconfig/libconic.pc
	ldconfig

clean:
	@ $(ECHO) RM "$(objects) $(host-objects) $(elf) $(lib)"
	@ $(RM) $(objects) $(host-objects) $(elf) $(lib)

distclean: clean
	@ $(ECHO) CLEAN *.o
	@ find . -type f -name '*.o' -exec rm {} \;

.PHONY: all library firmware size flash debug clean distclean

