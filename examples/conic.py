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

class SinkNotOpen(SinkException):
    pass

class Sink():
    __is_open = False

    def open(self, name):
        try:
            self.ll_open(name)
            self.__is_open = True
        except SinkException:
            self.__is_open = False
            raise SinkException

    def is_open(self):
        return self.__is_open

    def write(self, packet):
        if not self.is_open():
            raise SinkNotOpen

        self.ll_write(packet)

    def close(self):
        self.ll_close()

class DebugSink(Sink):
    def ll_open(self, name):
        pass

    def ll_write(self, packet):
        print('packet:', list(packet.bytes))

    def ll_close(self):
        pass

class SerialSink(Sink):
    serial_port = serial.Serial()

    def ll_open(self, name):
        try:
            self.serial_port.setPort(name)
            self.serial_port.open()
        except serial.SerialException:
            raise SinkNotOpen

    def ll_write(self, packet):
        self.serial_port.write(packet.bytes)

    def ll_close(self):
        self.serial_port.close()

"""
Device logic
"""

class DeviceException(Exception):
    pass

class DeviceNotFound(DeviceException):
    pass

class Device():
    sink = SerialSink()
    # sink = DebugSink()

    def __send_packet(self, payload):
        packet = Packet(payload)

        try:
            self.sink.write(packet)
        except SinkNotOpen:
            raise DeviceNotFound('Device is not connected')
        except SinkException:
            raise DeviceException('Unable to send packet')

    def connect(self, port_name):
        """Connect to remote device"""
        try:
            self.sink.open(port_name)
        except SinkException:
            raise DeviceNotFound('Unable to connect to %s' % port_name)

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

