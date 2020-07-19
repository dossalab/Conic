#!/bin/python

import serial
import random 
import sys 

def send_debug_packet():
    print("Sending debug packet...")

    # send some random junk - cool fifos will help us
    for i in range(random.randint(0, 10)):
        ser.write(b't')

    packet = [
        0xFF, # packet start
        0x00, # address
        0x44, # from the host
        0x00, # payload - debug (4 bytes)

        # ~~~~ payload ~~~~
        0x01, # led_on
        0x00, #
        0x00, #
        0x00, #
        0x00, #
        0x00, #
        0x00, #
        0x00, #
        0x00, #
        0x00, #
        0x00, #
        0x00, #
        0x00, #
        0x00, #
        0x00, #
        0x00, #
        0x00, #
        0x00, #
        0x00, #
        0x00, #
        0x00, #
        0x00, #
        0x00, #
        0x00, #

        0x00, # flags 0
        0x00, # flags 1
        0x00, # crc (not implemented)
        0xFF, # packet end
    ]

    ser.write(bytearray(packet))

    # send some random junk just for fun - cool fifos will help us
    ser.write(b'test')

shell_commands = {
    "debug" : send_debug_packet
}

def die(message):
    print(message)
    sys.exit(1)

def shell_proceed():
    i = input('# ')

    try:
        handle = shell_commands[i]
        handle()
    except:
        print("unknown command!")

try:
    ser = serial.Serial('/dev/ttyUSB0')
except:
    die('unable to open port!')

try:
    while True:
        shell_proceed()
except KeyboardInterrupt:
    pass

print("closing the port...")
ser.close()

