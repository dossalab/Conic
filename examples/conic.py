#
# Part of the Conic project - robot arm controller
#
# Simple library for conic control packages
#
# See LICENSE.md for licensing information
# Roman Luitko, 2020
#

import serial
import serial.tools.list_ports
import struct

# Common helper functions
class Manager():
    def list_ports():
        ports = []

        for port_info in serial.tools.list_ports.comports():
            ports.append(port_info.device)

        return ports

# Packet types from core/control.c
class PayloadType():
    DEBUG = 0
    MOTION = 1

class Packet():
    def __init__(self, payload_type, payload):
        self.type = payload_type

        # we probably should use some sort of bytearray for payload
        self.bytes = [
            0xFF, # packet start
            0x00, # address (not implemented)
            0x44, # from the host
            self.type, # payload type

            # ~~~~ payload ~~~~
            # XXX: insert payload here
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
            0x00, #

            0x00, # flags 0
            0x00, # flags 1
            0x00, # crc (not implemented)
            0xFF, # packet end
        ]

class DeviceNotFoundException(Exception):
    pass

class Device():
    ser = serial.Serial()

    def __send_packet(self, payload_type, payload):
        """Send packet over serial"""
        packet = Packet(payload_type, payload)
        print(packet.bytes)

    def connect(self, port_name):
        """Connect to remote device"""
        self.ser.setPort(port_name)

        try:
            self.ser.open()
        except:
            raise DeviceNotFoundException

    def disconnect(self):
        """Disconnect from the device"""
        self.ser.close()

    def is_connected(self):
        """Check device presense"""
        return self.ser.is_open

    def move(self, x, y, z, a):
        """Move arm to a new absolute position"""
        self.__send_packet(PayloadType.MOTION, \
                list(struct.pack("<ffff", x, y, z, a)))

    def park(self, x, y, z, a):
        """Park arm in some default, safe position"""
        pass

