/*
 * Part of the Conic project - robot arm controller
 *
 * serial_windows.c - serial port wrapper (windows)
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifdef _WIN32

#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "serial.h"

#define MAX_WINDOWS_HANDLES	16
static HANDLE windows_handles[MAX_WINDOWS_HANDLES];

static int store_windows_handle(HANDLE handle)
{
	static int current_handle;
	int fd = -1;

	if (current_handle < MAX_WINDOWS_HANDLES) {
		windows_handles[current_handle] = handle;
		fd = current_handle;
		current_handle++;
	}

	return fd;
}

static char *load_dos_devices(void)
{
	char *buffer = NULL, *new_buffer;
	int allocated = 0;
	const int alloc_amount = 64;

	SetLastError(0);

	for (;;) {
		if (QueryDosDeviceA(NULL, buffer, allocated) > 0) {
			break;
		}

		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
			new_buffer = realloc(buffer, allocated + alloc_amount);

			if (new_buffer) {
				buffer = new_buffer;
				allocated += alloc_amount;
				continue;
			}
		}

		if (buffer) {
			free(buffer);
			buffer = NULL;
		}

		break;
	}

	return buffer;
}

static bool contains_base(const char *string, const char *base)
{
	return (strncmp(string, base, strlen(base)) == 0);
}

int serial_enumerate(int (*callback)(const char *))
{
	char *devices, *device;
	int fd = -1;

	devices = load_dos_devices();
	if (!devices) {
		return -1;
	}

	device = devices;
	while (*device) {
		if (contains_base(device, "COM")) {
			fd = callback(device);
			if (fd >= 0) {
				break;
			}
		}

		device = strchr(device, '\0');
		device++;
	}

	free(devices);
	return fd;
}

static HANDLE get_windows_handle(int handle)
{
	if (handle >= 0 && handle < MAX_WINDOWS_HANDLES) {
		return windows_handles[handle];
	}

	return INVALID_HANDLE_VALUE;
}

int serial_write(int handle, const uint8_t *data, size_t len)
{
	unsigned long amount;
	HANDLE windows_handle;

	amount = 0;
	windows_handle = get_windows_handle(handle);
	WriteFile(windows_handle, (const void *)data, len, &amount, NULL);

	return amount;
}

int serial_read(int handle, uint8_t *data, size_t len)
{
	unsigned long amount;
	HANDLE windows_handle;

	amount = 0;
	windows_handle = get_windows_handle(handle);
	ReadFile(windows_handle, (void *)data, len, &amount, NULL);

	return amount;
}

int serial_open(const char *port_name, int baudrate)
{
	DCB config = {0};
	COMMTIMEOUTS timeouts = {0};
	HANDLE windows_handle;
	int handle;

	windows_handle = CreateFileA(port_name, GENERIC_READ | GENERIC_WRITE, \
					0, NULL, OPEN_EXISTING, 0, NULL);

	if (windows_handle == INVALID_HANDLE_VALUE) {
		return -1;
	}

	SetupComm(windows_handle, 64, 64);
	timeouts.ReadIntervalTimeout = 0;
	timeouts.ReadTotalTimeoutConstant = SERIAL_READ_TIMEOUT;
	timeouts.WriteTotalTimeoutConstant = 0;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.WriteTotalTimeoutMultiplier = 0;
	SetCommTimeouts(windows_handle, &timeouts);

	GetCommState(windows_handle, &config);
	config.BaudRate = baudrate;
	config.fBinary = TRUE;
	config.fParity = 0;
	config.fErrorChar = 0;
	config.fNull = 0;
	config.fAbortOnError = 0;
	config.ByteSize = 8;
	config.Parity = NOPARITY;
	config.StopBits = ONESTOPBIT;

	if (SetCommState(windows_handle, &config) == 0) {
		CloseHandle(windows_handle);
		return -1;
	}

	handle = store_windows_handle(windows_handle);
	if (handle < 0) {
		CloseHandle(windows_handle);
		return -1;
	}

	return handle;
}

void serial_close(int handle)
{
	HANDLE windows_handle;

	windows_handle = get_windows_handle(handle);
	CloseHandle(windows_handle);
}

#endif

