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

/* in milliseconds */
#define SERIAL_READ_TIMEOUT	100

/*
 * callback should return -1 to continue enumeration,
 * or positive value (valid file descriptor) to end it;
 * in that case serial_enumerate will return that descriptor
 */
int serial_enumerate(int (*callback)(const char *));

int serial_write(int handle, const uint8_t *data, size_t len);
int serial_read(int handle, uint8_t *data, size_t len);
int serial_open(const char *port_name, int baudrate);
bool serial_is_open(int fd);
void serial_close(int handle);

#endif

