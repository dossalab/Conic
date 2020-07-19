# We use allow-override here because CC and LD are set
# by make itself, so simpler ?= approach won't work

$(call allow-override,CC,arm-none-eabi-gcc)
$(call allow-override,LD,arm-none-eabi-gcc)
$(call allow-override,GDB,arm-none-eabi-gdb)
$(call allow-override,SIZE,arm-none-eabi-size)

# Verify that everything is set...
$(call check-defined, MARCH)
$(call check-defined, ARM_ROM_START)
$(call check-defined, ARM_RAM_START)
$(call check-defined, ARM_ROM_LENGTH)
$(call check-defined, ARM_RAM_LENGTH)

$(call check-defined, ARM_CORE_CLK)

this-dir := $(call my-dir)

LDFLAGS	+= \
	-specs=nosys.specs -specs=nano.specs -nostartfiles \
	-mthumb \
	-mcpu=$(MARCH)

CFLAGS += \
	-mthumb \
	-mcpu=$(MARCH) \
	-DARCH_LITTLE_ENDIAN \
	-DARM_CORE_CLK=$(ARM_CORE_CLK)

LDFLAGS += \
	-T$(this-dir)cortex-m.ld \
	-Wl,--defsym=__rom_start__=$(ARM_ROM_START) \
	-Wl,--defsym=__ram_start__=$(ARM_RAM_START) \
	-Wl,--defsym=__rom_length__=$(ARM_ROM_LENGTH) \
	-Wl,--defsym=__ram_length__=$(ARM_RAM_LENGTH)

objects += \
	$(this-dir)boot.o \
	$(this-dir)systick.o \
	$(this-dir)nvic.o

