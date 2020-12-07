"""
 Part of the Conic project - robot arm controller

 libconic wrapper for python. Wraps connection / disconnection and
 servo handling

 See LICENSE.md for licensing information
 Roman Luitko, 2020
"""

import os
from platform import platform
import ctypes

shared_extension = 'dll' if platform().startswith('win32') else 'so'
libconic = ctypes.CDLL(f'libconic.{shared_extension}')

class DeviceError(Exception):
    """libconic wrapper exception"""

class Servo:
    servo = -1

    def __init__(self, device, port, pin):
        """Create servo inside device"""
        if self.servo != -1:
            self.servo = libconic.conic_servo_init(device.handle)

    def move(self, pulse):
        libconic.conic_servo_move(self.handle, self.servo, pulse)

class Device:
    """libconic device wrapper"""
    handle = -1

    def execute_motion(self):
        """Start motion"""

    def check_presense(self):
        """Checks if device is here"""

    def open(self):
        """Connect to remote device"""
        if self.handle != -1:
            raise DeviceError('device is already open')

        self.handle = libconic.conic_device_open()
        if self.handle < 0:
            raise DeviceError('unable to open device')

    def close(self):
        """Disconnect from the device"""
        if self.handle != -1:
            self.libconic.conic_device_close(self.handle)
            self.handle = -1

