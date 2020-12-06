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
#include <string.h>

/* TODO: provide a configuration option for that */
#define ARCH_LITTLE_ENDIAN
#include <misc/endian.h>

static int enumerate_callback(const char *dev)
{
	int handle;

	handle = serial_open(dev, CONIC_BAUDRATE);
	if (handle < 0) {
		return -ENOENT;
	}

	if (conic_check_presense(handle) < 0) {
		serial_close(handle);
		return -ENOENT;
	}

	return handle;
}

static int send_packet(int handle, int packet_id, void *payload, size_t size)
{
	struct serial_packet packet;
	struct serial_packet answer;
	int written, read;

	packet_fill(&packet, packet_id);
	memcpy(packet.data, payload, size);

	written = serial_write(handle, &packet, sizeof(packet));
	if (written != sizeof(packet)) {
		return -ENOLINK;
	}

	read = serial_read(handle, &answer, sizeof(answer));
	if (read != sizeof(answer)) {
		return -ENOLINK;
	}

	if (answer.type != DEVICE_ANSWER_PID) {
		return -EINVAL;
	}

	return ((struct answer_payload *)answer.data)->retval;
}

int conic_servo_init(int handle, char port, int8_t pin)
{
	struct servo_init_payload payload;

	memset(&payload, 0, sizeof(payload));

	payload.pin = pin;
	payload.port = port;

	return send_packet(handle, SERVO_INIT_PID, &payload, sizeof(payload));
}

int conic_servo_move(int handle, uint8_t servo_handle, uint16_t pulse)
{
	struct servo_move_payload payload;

	memset(&payload, 0, sizeof(payload));

	payload.servo = servo_handle;
	payload.pulse = cpu_to_le16(pulse);

	return send_packet(handle, SERVO_MOVE_PID, &payload, sizeof(payload));
}

int conic_execute_motion(int handle)
{
	struct execute_motion_payload payload;

	memset(&payload, 0, sizeof(payload));
	/* no arguments */

	return send_packet(handle, EXECUTE_MOTION_PID, &payload, sizeof(payload));
}

int conic_check_presense(int handle)
{
	struct check_presense_payload payload;

	memset(&payload, 0, sizeof(payload));

	return send_packet(handle, CHECK_PRESENSE_PID, &payload, sizeof(payload));
}

int conic_device_open(void)
{
	return serial_enumerate(enumerate_callback);
}

void conic_device_close(int handle)
{
	if (handle >= 0) {
		serial_close(handle);
	}
}

