/*
 * Part of the Conic project - robot arm controller
 *
 * serial_unix.c - serial port wrapper (unix)
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#if defined(__unix__) || defined(__unix)

#include <unistd.h>
#include <stdint.h>
#include <termios.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "serial.h"

static const char *serial_bases[] = {
	"ttyACM", "ttyUSB", NULL
};

static int baudrate_to_flags(int baudrate)
{
	switch (baudrate) {
		case 50:	return B50;
		case 110:	return B110;
		case 134:	return B134;
		case 150:	return B150;
		case 200:	return B200;
		case 300:	return B300;
		case 600:	return B600;
		case 1200:	return B1200;
		case 1800:	return B1800;
		case 2400:	return B2400;
		case 4800:	return B4800;
		case 9600:	return B9600;
		case 19200:	return B19200;
		case 38400:	return B38400;
		case 57600:	return B57600;
		case 115200:	return B115200;
		case 230400:	return B230400;
		default:	return -1;
	}
}

static bool contains_base(const char *string, const char *base)
{
	return (strncmp(string, base, strlen(base)) == 0);
}

int serial_enumerate(int (*callback)(const char *))
{
	DIR *dev;
	struct dirent *node;
	const char **base_ptr, *base;
	int fd = -1;

	dev = opendir("/dev");
	if (!dev) {
		return -1;
	}

	while ((node = readdir(dev))) {
		base_ptr = serial_bases;

		while ((base = *(base_ptr++))) {
			if (!contains_base(node->d_name, base)) {
				continue;
			}

			fd = callback(node->d_name);
			if (fd >= 0) {
				goto exit;
			}

		}
	}

exit:
	closedir(dev);
	return fd;
}

int serial_write(int fd, const uint8_t *data, size_t len)
{
	return write(fd, data, len);
}

int serial_read(int fd, uint8_t *data, size_t len)
{
	return read(fd, data, len);
}

int serial_open(const char *port_name, int baudrate)
{
	int handle, baud_flags;
	struct termios config;

	baud_flags = baudrate_to_flags(baudrate);
	if (baud_flags < 0) {
		return -1;
	}

	handle = open(port_name, O_RDWR | O_NOCTTY | O_NDELAY);
	if (handle < 0) {
		return -1;
	}

	memset(&config, 0, sizeof(config));
	tcgetattr(handle, &config);

	config.c_iflag &= ~(INLCR | ICRNL);
	config.c_iflag |= IGNPAR | IGNBRK;
	config.c_oflag &= ~(OPOST | ONLCR | OCRNL);
	config.c_cflag &= ~(PARENB | PARODD | CSTOPB | CSIZE | CRTSCTS);
	config.c_cflag |=  CLOCAL | CREAD | CS8;
	config.c_lflag &= ~(ICANON | ISIG | ECHO);

	config.c_cc[VTIME] = SERIAL_READ_TIMEOUT / 100;
	config.c_cc[VMIN]  = 0;

	cfsetospeed(&config, baud_flags);
	cfsetispeed(&config, baud_flags);

	if (tcsetattr(handle, TCSANOW, &config) < 0) {
		close(handle);
		return -1;
	}

	return handle;
}

void serial_close(int fd)
{
	tcdrain(fd);
	close(fd);
}

#endif

