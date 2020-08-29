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
	echo "Usage $0 [gdb] [chip] [adapter] [file]"
	exit 1
}

[ $# -ne 4 ] && print_usage

GDB=$1
DEBUG_CHIP=$2
DEBUG_ADAPTER=$3
DEBUG_FILE=$4

[ ! -f $DEBUG_FILE ] && die "File $DEBUG_FILE does not exist!"

$GDB $DEBUG_FILE -ex "target extended-remote | \
	openocd -f 'interface/$DEBUG_ADAPTER.cfg' \
		-f 'target/$DEBUG_CHIP.cfg' \
		-c 'gdb_port pipe'"

