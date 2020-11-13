/*
 * Part of the Conic project - robot arm controller
 *
 * libconic - PC interfacing library
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include "libconic.h"
#include <host/serial.h>
#include <proto/messages.h>
#include <proto/packet.h>
#include <misc/endian.h>
#include <string.h>

static int enumerate_callback(const char *dev)
{
	return serial_open(dev, CONIC_BAUDRATE);
}

int conic_open(void)
{
	return serial_enumerate(enumerate_callback);
}

int conic_is_open(int fd)
{
	if (!serial_is_open(fd)) {
		return -1;
	}

	return 0;
}

int conic_move(int fd, int16_t x, int16_t y, int16_t z)
{
	struct serial_packet packet;
	struct move_packet_payload payload;
	int written;

	payload.x = cpu_to_le16(x);
	payload.y = cpu_to_le16(y);
	payload.z = cpu_to_le16(z);

	packet_fill(&packet, MOVE_PACKET_ID);
	memcpy(packet.data, &payload, sizeof(struct move_packet_payload));

	written = serial_write(fd, (const uint8_t *)&packet, sizeof(packet));
	if (written != sizeof(packet)) {
		return -1;
	}

	return 0;
}

int conic_park(int fd, int16_t x, int16_t y, int16_t z)
{
	return -1;
}

void conic_close(int fd)
{
	serial_close(fd);
}

