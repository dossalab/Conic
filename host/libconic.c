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

#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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

static float truncate(float value, float min, float max)
{
	if (value < min) {
		return min;
	}

	if (value > max) {
		return max;
	}

	return value;
}

/* basically convert to milli-radians or something like that */
static int16_t float_radians_to_fixed(float r)
{
	return 1000 * truncate(r, 0, 2 * M_PI);
}

int conic_move(int fd, float s1, float s2, float s3,
		float s4, float s5, float s6)
{
	struct serial_packet packet;
	struct move_packet_payload payload;
	int written;

	uint16_t fp_s1 = float_radians_to_fixed(s1);
	uint16_t fp_s2 = float_radians_to_fixed(s2);
	uint16_t fp_s3 = float_radians_to_fixed(s3);
	uint16_t fp_s4 = float_radians_to_fixed(s4);
	uint16_t fp_s5 = float_radians_to_fixed(s5);
	uint16_t fp_s6 = float_radians_to_fixed(s6);

	payload.s1 = cpu_to_le16(fp_s1);
	payload.s2 = cpu_to_le16(fp_s2);
	payload.s3 = cpu_to_le16(fp_s3);
	payload.s4 = cpu_to_le16(fp_s4);
	payload.s5 = cpu_to_le16(fp_s5);
	payload.s6 = cpu_to_le16(fp_s6);

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

