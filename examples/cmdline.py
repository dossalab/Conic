#!/bin/python

#
# Part of the Conic project - robot arm controller
#
# Sample shell-like application using conic library
#
# See LICENSE.md for licensing information
# Roman Luitko, 2020
#

import cmd
import conic
import colorama
from signal import signal, SIGINT

class printer():
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

    def e(message):
        print(printer.colored('*** error -', 'red'), message)

    def i(message):
        print(printer.colored('*', 'blue'), message)

class App(cmd.Cmd, conic.Device):
    prompt = printer.colored('[conic] ', 'yellow')
    intro = 'Example Conic shell. Type help for available commands'

    def do_connect(self, port):
        """connect [port] - connect to the conic device"""
        if self.is_connected():
            printer.e('device is already connected')
            return False

        if not port:
            printer.e('expected port name')
            return False

        try:
            self.connect(port)
        except conic.DeviceNotFoundException:
            printer.e('unable to connect to %s!' % (port))

    def do_disconnect(self, line):
        """disconnect - disconnect from the conic device"""
        if not self.is_connected():
            printer.e('device is not connected')
            return False

        self.disconnect()

    def do_move(self, line):
        """move [x y z a] - position arm"""
        if not self.is_connected():
            printer.e('device is not connected')
            return False

        pos = line.split()

        if (len(pos) != 4):
            printer.e('expected 4 coordinates, %d were given' % (len(pos)))
            return False

        x = float(pos[0])
        y = float(pos[1])
        z = float(pos[2])
        a = float(pos[3])

        printer.i('moving arm to (%f %f %f %f)' % (x, y, z, a))
        self.move(x, y, z, a)

    def do_park(self, line):
        """park - position arm at park position"""
        if not self.is_connected():
            printer.e('device is not connected')
            return False

        self.park()

    def do_exit(self, line):
        """exit - disconnect everything and exit application"""
        self.disconnect()
        return True

    def default(self, line):
        printer.e('\'%s\': no such command (try \'help\')' % (line))

if __name__ == '__main__':
    colorama.init()
    app = App()

    def ctrlc_handler(signal_received, frame):
        app.disconnect()
        exit(0)

    signal(SIGINT, ctrlc_handler)
    app.cmdloop()

