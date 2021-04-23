[![Build Status](https://travis-ci.org/dossalab/Conic.svg?branch=master)](https://travis-ci.org/dossalab/Conic)

# Conic - robot servo controller (WIP)

This project aims to create a servo controller. Currently we're able to generate signals for 6 (and probably much more) servos. This software is by-design cross-platform, and targeted to 32-bit cortex-m microcontrollers like NRF52 or STM32, yet provide some sort of compability to old AVRs (Arduino).
This project is currently used to drive a 6-axis robotic arm. 

## Abstract

Hardware used inside the robot is based on STM32 blue pill (STM32F103). It communicates over serial to a PC (or raspberry pi, or anything, doesn't really matter) We use library called libconic at the host side to control servos. It's written in C, so it can be easily binded to any high-level language. We provide python wrapper as an (functional) example.

## Building the firmware

Build system is based on make. Building Conic requires some sort of bare-metal cross compiler. Since we already support 2 architectures here, you'll need `avr-gcc` for Arduino / AVR build and something like `arm-none-eabi-gcc` for ARM-based boards. To build a project, export `BOARD` enviromental variable, like `export BOARD=arduino_v1` (see boards directory for list of available boards). Then you can do `make`. conic.elf is your firmware.

## Flashing / running the firmware

You can also flash firmware using make by `make flash`.

### Arduino boards

Arduino is flashed over serial bootloader, and it's impossible to tell which serial port it uses. Script will try to autodetect it using list of predefined ports, but in some cases it may fail. You can set `FLASH_AVRDUDE_PORT` enviromental variable to set required port.

### ARM-based boards

To flash ARM-based board or, generally, non-arduino board you should set `FLASH_ADAPTER` enviromental variable, or, more easily, call make like this: `FLASH_ADAPTER=stlink make flash`. That will use STLink (available on AliExpress for 2$) adapter for flashing. `FLASH_ADAPTER` is passed directly to openocd, so consult openocd manuals for list of available adapters. If you are using older openocd, it very well may be called stlink-v2 or something like this.

## Interfacing with firmware

You can install python package using pip - for example `pip install https://github.com/dossalab/Conic/archive/refs/tags/conic-1.0.2.tar.gz`. Please make sure you have C/C++ compiler installed. On Windows, you may need to download SDK and Visual Studio together with 'Desktop C/C++ workload'. Refer to official python documentation on C extensions in order to get recent information.

Python library usage can be illustrated with a simple example:
```
import pyconic

p = pyconic.Conic()
p.open()
p.move(0, 0, 0, 0, 0, 0) # 6 angles, in radians
p.close()
```

## envsetup.sh

There are quite a lot of environmental variables used during the build, you may want to set all of them simultaneously. Please refer to `envsetup-sample.sh` - you can copy it to `envsetup.sh` or something, modify it according to your board and source it like that: `source ./envsetup.sh`
