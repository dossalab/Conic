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

int conic_move(int fd, int16_t s1, int16_t s2, int16_t s3,
		int16_t s4, int16_t s5, int16_t s6)
{
	struct serial_packet packet;
	struct move_packet_payload payload;
	int written;

	payload.s1 = cpu_to_le16(s1);
	payload.s2 = cpu_to_le16(s2);
	payload.s3 = cpu_to_le16(s3);
	payload.s4 = cpu_to_le16(s4);
	payload.s5 = cpu_to_le16(s5);
	payload.s6 = cpu_to_le16(s6);

	packet_fill(&packet, MOVE_PACKET_ID);
	memcpy(packet.data, &payload, sizeof(struct move_packet_payload));

	written = serial_write(fd, (const uint8_t *)&packet, sizeof(packet));
	if (written != sizeof(packet)) {
		return -1;
	}

	return 0;
}

void conic_close(int fd)
{
	serial_close(fd);
}

