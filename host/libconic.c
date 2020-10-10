/*
 * Part of the Conic project - robot arm controller
 *
 * libconic - PC interfacing library
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <host/serial.h>

#ifdef _WIN32
  #define API_EXPORT __declspec(dllexport)
#else
  #define API_EXPORT
#endif

#define CONIC_BAUDRATE	115200

static int enumerate_callback(const char *dev)
{
	return serial_open(dev, CONIC_BAUDRATE);
}

int API_EXPORT conic_open(void)
{
	return serial_enumerate(enumerate_callback);
}

void API_EXPORT conic_close(int fd)
{
	serial_close(fd);
}

