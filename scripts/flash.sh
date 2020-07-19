#!/bin/sh

#
# Part of the Conic project - robot arm controller
#
# See LICENSE.md for licensing information
# Roman Luitko, 2020
#

die() {
	echo $1
	exit 1
}

print_usage() {
	echo "Usage $0 [chip] [programmer] [file]"
	exit 1
}

[ $# -ne 3 ] && print_usage

FLASH_CHIP=$1
FLASH_ADAPTER=$2
FLASH_FILE=$3

AVRDUDE_PORTS="/dev/ttyUSB0 /dev/ttyACM0"

[ ! -f $FLASH_FILE ] && die "File $FLASH_FILE does not exist!"

case $FLASH_CHIP in
nrf52 | stm32f1x)
	echo "Using openocd flashing for ARM target..."
	openocd -f "interface/$FLASH_ADAPTER.cfg" \
		-f "target/$FLASH_CHIP.cfg" \
		-c "program $FLASH_FILE; reset; exit"
	;;
atmega328*)
	echo "Using Avrdude for AVR target..."

	if [ $FLASH_ADAPTER = "arduino" ]; then
		if [ -z $FLASH_AVRDUDE_PORT ]; then
			echo "FLASH_AVRDUDE_PORT is not set... Trying to guess"

			for port in $AVRDUDE_PORTS; do
				echo Trying $port...

				if [ -c $port ]; then
					echo "Port $port exists"
					FLASH_AVRDUDE_PORT=$port
					break;
				fi
			done

			[ -z $FLASH_AVRDUDE_PORT ] && die "Unable to autodetect \
				port! Please set FLASH_AVRDUDE_PORT"
		fi

		avrdude -p $FLASH_CHIP -c $FLASH_ADAPTER \
			-P $FLASH_AVRDUDE_PORT \
			-U flash:w:$FLASH_FILE
	else
		avrdude -p $FLASH_CHIP -c $FLASH_ADAPTER \
			-U flash:w:$FLASH_FILE
	fi

	exit $?
	;;
*)
	die "Unsupported chip!"
	;;
esac

