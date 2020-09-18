#!/bin/env python3

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
import argparse
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

    def __init__(self, args):
        super().__init__()

        if args.port:
            self.connect(args.port)

    def do_connect(self, port):
        """connect [port] - connect to the conic device"""
        if not port:
            printer.e('expected port name')
            return False

        try:
            self.connect(port)
        except conic.DeviceException as e:
            printer.e(e)

    def do_disconnect(self, line):
        """disconnect - disconnect from the conic device"""
        try:
            self.disconnect()
        except conic.DeviceException as e:
            printer.e(e)

    def do_connected(self, line):
        """connected - are we connected or not?"""
        printer.i(self.is_connected())

    def do_move(self, line):
        """move [x y z] - position arm"""
        pos = line.split()

        if (len(pos) != 3):
            printer.e('expected 3 coordinates, %d were given' % (len(pos)))
            return False

        try:
            x = int(pos[0])
            y = int(pos[1])
            z = int(pos[2])
        except ValueError:
            printer.e('unable to parse coordinates')
            return False

        printer.i('moving arm to (%f %f %f)' % (x, y, z))

        try:
            self.move(x, y, z)
        except conic.DeviceException as e:
            printer.e(e)

    def do_park(self, line):
        """park - position arm at park position"""
        try:
            self.park()
        except conic.DeviceException as e:
            printer.e(e)

    def do_exit(self, line):
        """exit - disconnect everything and exit application"""
        self.disconnect()
        return True

    def default(self, line):
        printer.e('\'%s\': no such command (try \'help\')' % (line))

def handle_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('-p', '--port', help='connect to a port on startup')

    return parser.parse_args()

if __name__ == '__main__':
    colorama.init()
    args = handle_args()

    try:
        app = App(args)
    except Exception as e:
        printer.e(e)
        exit(1)

    def ctrlc_handler(signal_received, frame):
        app.disconnect()
        exit(0)

    signal(SIGINT, ctrlc_handler)
    app.cmdloop()

