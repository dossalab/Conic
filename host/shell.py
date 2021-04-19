#!/usr/bin/env python3

"""
 Part of the Conic project - robot arm controller

 Sample shell-like application using libconic

 See LICENSE.md for licensing information
 Roman Luitko, 2020
"""

import cmd
import ctypes
import os
import sys
from platform import platform
import signal
import colorama

class Printer:
    """simple wrapper around io, just to make it centralized"""

    @staticmethod
    def colored(message, color):
        """fairly autistic text colorizer"""
        ansi_stop = colorama.Style.RESET_ALL

        if color == 'red':
            ansi_start = colorama.Fore.RED
        elif color == 'blue':
            ansi_start = colorama.Fore.BLUE
        elif color == 'yellow':
            ansi_start = colorama.Fore.YELLOW
        elif color == 'green':
            ansi_start = colorama.Fore.GREEN
        else:
            raise Exception('unknown color %s' % (color))

        return f'{ansi_start}{message}{ansi_stop}'

    @staticmethod
    def e(message):
        """error message"""
        print(Printer.colored('*** error -', 'red'), message)

    @staticmethod
    def i(message):
        """info message"""
        print(Printer.colored('*', 'blue'), message)

class WrapperException(Exception):
    """libconic wrapper exception"""

class Wrapper:
    """libconic wrapper"""
    extension = 'dll' if platform().startswith('win32') else 'so'
    respath = os.path.join(os.path.dirname(__file__), 'libconic.%s' % extension)
    libconic = ctypes.CDLL(respath)
    handle = -1

    def open(self):
        """Connect to remote device"""
        if self.handle != -1:
            raise WrapperException('device is already open')

        self.handle = self.libconic.conic_open()
        if self.handle < 0:
            raise WrapperException('unable to open device')

    def close(self):
        """Disconnect from the device"""
        if self.handle != -1:
            self.libconic.conic_close(self.handle)
            self.handle = -1

    def is_open(self):
        """Check device presense"""
        ret = self.libconic.conic_is_open(self.handle)
        if ret < 0:
            return False

        return True

    def move(self, x, y, z):
        """Move arm to a new absolute position"""
        ret = self.libconic.conic_move(self.handle, x, y, z)
        if ret < 0:
            raise WrapperException('unable to move arm')

class App(cmd.Cmd, Wrapper):
    """sample shell application - demonstrates libconic usage"""
    prompt = Printer.colored('[conic] ', 'yellow')
    conic = Wrapper()
    intro = 'Example Conic shell. Type help for available commands'

    def __init__(self):
        super().__init__()

        try:
            self.conic.open()
            Printer.i('Port opened successfully')
        except WrapperException as e:
            Printer.e(e)

    def do_open(self, _):
        """open - connect to the conic device"""
        try:
            self.conic.open()
        except WrapperException as e:
            Printer.e(e)

    def do_close(self, _):
        """close - disconnect from the conic device"""
        try:
            self.conic.close()
        except WrapperException as e:
            Printer.e(e)

    def do_is_open(self, _):
        """is_open - are we connected or not?"""
        Printer.i(self.is_open())

    def do_move(self, line):
        """move [x y z] - position arm"""
        pos = line.split()

        if len(pos) != 3:
            Printer.e('expected 3 coordinates, %d were given' % (len(pos)))
            return

        try:
            x = int(pos[0])
            y = int(pos[1])
            z = int(pos[2])
        except ValueError:
            Printer.e('unable to parse coordinates')
            return

        Printer.i('moving arm to (%f %f %f)' % (x, y, z))

        try:
            self.conic.move(x, y, z)
        except WrapperException as e:
            Printer.e(e)

    def do_exit(self, _):
        """exit - disconnect everything and exit application"""
        self.conic.close()
        return True

    def default(self, line):
        Printer.e('\'%s\': no such command (try \'help\')' % (line))

if __name__ == '__main__':
    colorama.init()
    app = App()

    def ctrlc_handler(signal_number, _):
        """handle application exit"""
        Printer.i('got signal %s, exiting...' % signal_number)
        app.do_exit('')
        sys.exit(0)

    signal.signal(signal.SIGINT, ctrlc_handler)
    app.cmdloop()

