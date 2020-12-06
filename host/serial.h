/*
 * Part of the Conic project - robot arm controller
 *
 * common serial platform-independent api
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef HOST_SERIAL_H
#define HOST_SERIAL_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define SERIAL_READ_TIMEOUT	100 /* milliseconds */

/*
 * Scans list of available ports, calls callback for each of them
 *
 * args:
 *   callback - pointer to user function (int ...(const char *portname)).
 *            callback should return negative value to continue enumeration,
 *            or positive value (valid file descriptor) to end it
 *
 * return:
 *   if callback returns positive value, function will return that value;
 *   negative value otherwise
 */
int serial_enumerate(int (*callback)(const char *));

/*
 * For both read and write:
 *
 * args:
 *   handle - serial port handle (see serial_open)
 *   data - pointer to buffer with/for data
 *   len - length of the buffer
 *
 * return: number of bytes read / written, or negative value in case of an error
 */
int serial_write(int handle, const void *data, size_t len);
int serial_read(int handle, void *data, size_t len);

/*
 * Opens a given port_name with baudrate. port_name is '/dev/ttyX' on linux,
 * COMx on windows. Note that ports higher than 9 should look like \\.\COMx
 *
 * return: port handle (integer) or negative value in case of an error
 */
int serial_open(const char *port_name, int baudrate);

/*
 * Flush and close the port. handle is serial port handle (see serial_open)
 */
void serial_close(int handle);

#endif

