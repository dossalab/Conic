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

"""
packet format (copy from core/serial.c)

+-----------------+--------------------+-----------------+
| header(2 bytes) | payload (12 bytes) |  tail(2 bytes)  |
+--------+--------+--------------------+--------+--------+
|  0xFF  |  type  |   ~~~~ data ~~~~   |  CRC   |  0xFF  |
+--------+--------+--------------------+--------+--------+

off
 0: 0xFF	- start token
 1: type	- packet type
 2: data	- payload (12 bytes)
14: crc	        - crc7 of the packet
15: 0xFF	- end token
"""

class Packet():
    fmt = '<BB xxxx xxxx xxxx BB'

    def __init__(self, payload):
        self.bytes = bytearray(struct.pack(
            self.fmt,
            0xFF,
            payload.pid,
            0x00,
            0xFF)
        )

        # TODO: find a better way. yeah, that is stupid idea
        for i in range(len(payload.bytes)):
            self.bytes[2 + i] = payload.bytes[i]

"""
Payload formats
"""

class MotionPayload():
    """
    payload format:
    +---------+---------+---------+
    | 2 bytes | 2 bytes | 2 bytes |
    +---------+---------+---------+
    |  x pos  |  y pos  |  z pos  |
    +---------+---------+---------+
    """

    fmt = '<hhh'
    pid = 0x11

    def __init__(self, x, y, z):
        self.bytes = struct.pack(self.fmt, x, y, z)

class PresensePayload():
    """
    payload format:
    +---------+
    | 1 byte  |
    +---------+
    |  0xAA   |
    +---------+
    """
    fmt = '<B'
    pid = 0x17

    def __init__(self, x, y, z):
        self.bytes = struct.pack(self.fmt, x, y, z)

"""
Sinks (packet transmitters)

"""

class SinkException(Exception):
    pass

class DebugSink:
    def open(self, name):
        pass

    def is_open(self):
        return True

    def write(self, packet):
        print('packet:', list(packet.bytes))

    def close(self):
        pass

class SerialSink:
    serial_port = serial.Serial()

    def open(self, name):
        try:
            self.serial_port.setPort(name)
            self.serial_port.open()
        except serial.SerialException as e:
            raise SinkException('unable to open %s' % (name))

    def is_open(self):
        return self.serial_port.is_open

    def write(self, packet):
        try:
            self.serial_port.write(packet.bytes)
        except serial.SerialException as e:
            self.close()
            raise SinkException('unable to write to sink (%s)' % (e))

    def close(self):
        self.serial_port.close()

"""
Device logic
"""

class DeviceException(Exception):
    pass

class Device():
    sink = SerialSink()
    # sink = DebugSink()

    def __send_packet(self, payload):
        packet = Packet(payload)

        try:
            self.sink.write(packet)
        except SinkException as e:
            raise DeviceException(e)

    def connect(self, port_name):
        """Connect to remote device"""
        try:
            self.sink.open(port_name)
        except SinkException as e:
            raise DeviceException(e)

    def disconnect(self):
        """Disconnect from the device"""
        self.sink.close()

    def is_connected(self):
        """Check device presense"""
        return self.sink.is_open()

    def move(self, x, y, z):
        payload = MotionPayload(x, y, z)
        self.__send_packet(payload)
        """Move arm to a new absolute position"""

    def park(self):
        """Park arm in some default, safe position"""
        pass

