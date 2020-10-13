/*
 * Part of the Conic project - robot arm controller
 *
 * Packet is a container for chunks of data
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef PROTO_PACKET_H
#define PROTO_PACKET_H

#include <string.h> /* for memset */

/*
 * 16-byte control packets
 * Payload is type-specific. Users are free to pack any data there
 *
 * +-----------------+--------------------+-----------------+
 * | header(2 bytes) | payload (12 bytes) |  tail(2 bytes)  |
 * +--------+--------+--------------------+--------+--------+
 * |  0xFF  |  type  |   ~~~~ data ~~~~   |  CRC   |  0xFF  |
 * +--------+--------+--------------------+--------+--------+
 *
 * off
 *  0: 0xFF	- start token
 *  1: type	- packet type
 *  3: data	- payload (12 bytes)
 * 14: crc	- crc7 of the packet
 * 15: 0xFF	- end token
 */

#define SERIAL_PACKET_SIZE	16
#define SERIAL_PAYLOAD_SIZE	12

struct serial_packet {
	uint8_t start;
	uint8_t type;
	uint8_t data[SERIAL_PAYLOAD_SIZE];
	uint8_t crc;
	uint8_t end;
};

static inline void packet_fill(struct serial_packet *packet, uint8_t type)
{
	memset(packet, 0, sizeof(struct serial_packet));

	packet->start = 0xFF;
	packet->type = type;
	packet->end = 0xFF;
}

#endif

