# Conic - robot arm firmware (WIP)

This firmware should allow robotic arm to perform basic movements, controlled by UART from PC (or from external remote, may be?) This thing is by-design cross-platform, and targeted to 32-bit cortex-m microcontrollers like NRF52 or STM32, hence provide some sort of compability to old AVRs.

## Abstract

For now we lean tovards Arduino UNO R3 connected to a PC with a small python utility controlling it. Open questions are:
+ How to position arm? WASD or mouse or via blind coordinates?
+ Servos need some sort of torque protection, espesially on claw. We anyway need some sort of custom shield / board to implement at least current sensing. Is it better to design a shield for a more modern board with wireless MCU like NRF52 / ESP32?

## Building the firmware

Build system is based on make. Building Conic requires some sort of bare-metal cross compiler. Since we already support 2 architectures here, you'll need `avr-gcc` for Arduino / AVR build and something like `arm-none-eabi-gcc` for ARM-based boards. To build a project, export `BOARD` enviromental variable, like `export BOARD=arduino_v1` (see boards directory for list of available boards). Then you can do `make`. conic.elf is your firmware.

## Flashing / running the firmware

You can also flash firmware using make by `make flash`.

### Arduino boards

Arduino is flashed over serial bootloader, and it's impossible to tell which serial port it uses. Script will try to autodetect it using list of predefined ports, but in some cases it may fail. You can set `FLASH_AVRDUDE_PORT` enviromental variable to set required port.

### ARM-based boards

To flash ARM-based board or, generally, non-arduino board you should set `FLASH_ADAPTER` enviromental variable, or, more easily, call make like this: `FLASH_ADAPTER=stlink make flash`. That will use STLink (available on AliExpress for 2$) adapter for flashing. `FLASH_ADAPTER` is passed directly to openocd, so consult openocd manuals for list of available adapters. If you are using older openocd, it very well may be called stlink-v2 or something like this.

## Interfacing with firmware

You can refer to python examples in `examples` folder
For a quick demo you can call `make shell` - that will execute `examples/cmdline.py`. Also make sure you've set `SHELL_PORT`

## envsetup.sh

There are quite a lot of environmental variables used during the build, you may want to set all of them simultaneously. Please refer to `envsetup-sample.sh` - you can copy it to `envsetup.sh` or something, modify it according to your board and source it like that: `source ./envsetup.sh`

## Plans / thoughts

We can design a small joystick-like device with a couple of knobs and buttons. As it turns out, controlling this type of robots with a special input device works much better. Also we can put a small screen on it and use this device to record movements (Position arm, press some checkpoint button, move arm to next position, press checkpoint button, etc...), and then store, share and replay them.

## TODO's (not in priority)

### Cross-compilation

+ Getting builds on windows will be a huge pain since obtaining a gcc compiler is not as easy as obtaining it from a package manager. If somebody bundled make + some shell utilities + arm-gcc in one windows installer that'll be a life-saver.
+ Move to some sort of cross-platform build system (it should be pretty fast - not some java utility that takes 2 seconds to even load. Also it should support some sort of configuration).

