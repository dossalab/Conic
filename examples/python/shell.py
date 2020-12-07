#!/usr/bin/env python3

"""
 Part of the Conic project - robot arm controller

 Sample shell-like application using libconic

 See LICENSE.md for licensing information
 Roman Luitko, 2020
"""

import cmd
import os
import sys
import signal
import colorama
import libconic

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

class App(cmd.Cmd):
    """sample shell application - demonstrates libconic usage"""
    prompt = Printer.colored('[conic] ', 'yellow')
    device = libconic.Device()
    intro = 'Example Conic shell. Type help for available commands'

    def __init__(self):
        super().__init__()

        try:
            self.device.open()
            Printer.i('Port opened successfully')
        except libconic.DeviceError as e:
            Printer.e(e)

    def do_open(self, _):
        """open - connect to the conic device"""
        try:
            self.device.open()
        except libconic.DeviceError as e:
            Printer.e(e)

    def do_close(self, _):
        """close - disconnect from the conic device"""
        try:
            self.device.close()
        except libconic.DeviceError as e:
            Printer.e(e)

    def do_exit(self, _):
        """exit - disconnect everything and exit application"""
        self.device.close()
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

