/*
 * Part of the Conic project - robot arm controller
 *
 * ARM cortex-m universal linker script
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

/* LD_ROM_START, LD_RAM_START, etc defined for particular MCU */
MEMORY
{
	rom(rx) : ORIGIN = __rom_start__, LENGTH = __rom_length__
	ram(rwx) : ORIGIN = __ram_start__, LENGTH = __ram_length__
}

STACK_SIZE = 2K;
ENTRY(reset_handler)

SECTIONS
{
	. = ORIGIN(rom);

	.isr_vectors : {
		KEEP(*(.isr_vectors))
		KEEP(*(.mcu_isr_vectors))
	} >rom

	.text : {
		. = ALIGN(4);
		*(.text*)
		. = ALIGN(4);
		*(.rodata*)
	} >rom

	. = ORIGIN(ram);

	/* Stack is placed before ram, that should be safer */
	.stack (NOLOAD) : {
		. = ALIGN(8);
		. = . + STACK_SIZE;
		. = ALIGN(8);
		__stack__  = .;
	} > ram

	__data_load__ = LOADADDR(.data);
	.data : {
		__data_start__ = .;
		*(.data*)
		. = ALIGN(4);
		__data_end__ = .;
	} >ram AT >rom

	.bss (NOLOAD) : {
		__bss_start__ = .;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end__ = .;
	} >ram

	. = ALIGN(4);
	end = .;
}

