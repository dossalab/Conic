#
# Part of the Conic project - robot arm controller
#
# See LICENSE.md for licensing information
# Roman Luitko, 2020
#

include scripts/build.mk

$(call check-defined, BOARD, See 'board' directory for available boards)

ECHO	:= echo -e

out	:= conic.elf
objects	:= \
	core/arm.o \
	core/control.o \
	core/main.o \
	core/tasks.o \
	mcu/common.o \
	misc/crc7.o \
	drivers/servo.o

# FIXME: is -Wno-discarded-qualifiers really a good idea?
CFLAGS	:= \
	-Wall \
	-Wshadow \
	-Wno-main \
	-Wno-discarded-qualifiers \
	-I. -g3 -Og \
	-fdata-sections -ffunction-sections

LDFLAGS	:= -Wl,--gc-sections

include board/$(BOARD)/board.mk
$(call check-defined, MCU, Probably you have selected unsupported board!)

include mcu/$(MCU)/mcu.mk
$(call check-defined, ARCH)

include arch/$(ARCH)/arch.mk

# MCU_SPECIFIC_HEADER contains mcu-specific stuff
# Usually inits are hardware-specific, peripheral api is common
CFLAGS	+= -DMCU_SPECIFIC_HEADER="<mcu/$(MCU)/mcu.h>"

# Board-specific header will contain definitions that rest of the program
# can use (where is leds, where are buttons, etc...)
CFLAGS	+= -DBOARD_SPECIFIC_HEADER="<board/$(BOARD)/board.h>"

# ARCH-specific header will contain at least way to disable/enable interrupts
# to implement some sort of locking
CFLAGS	+= -DARCH_SPECIFIC_HEADER="<arch/$(ARCH)/arch.h>"

# Export ARCH, MCU, BOARD to C preprocessor just in case...
CFLAGS	+= -DARCH_$(ARCH) -DMCU_$(MCU) -DBOARD_$(BOARD)

all: $(out) size

%.o : %.c
	@ $(ECHO) "[CC]\t$@"
	@ $(CC) $(CFLAGS) -c $< -o $@

$(out) : $(objects)
	@ $(ECHO) "[LD]\t$@"
	@ $(LD) $(LDFLAGS) $^ -o $@

size:
	@ $(SIZE) $(out)

flash: $(out)
	$(call check-defined, FLASH_CHIP)
	$(call check-defined, FLASH_ADAPTER)

	@ $(ECHO) "[FLASH]\t$^"
	@ scripts/flash.sh $(FLASH_CHIP) $(FLASH_ADAPTER) $<

clean:
	@ $(ECHO) "[RM]\t$(objects) $(out)"
	@ $(RM) $(objects) $(out)

distclean: clean
	@ $(ECHO) "[CLEAN]"
	@ find . -type f -name '*.o' -exec rm {} \;

.PHONY: all size flash debug clean distclean

