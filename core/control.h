/*
 * Part of the Conic project - robot arm controller
 *
 * External commands handler
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef CORE_CONTROL_H
#define CORE_CONTROL_H

#include <stdint.h>
#include <stdbool.h>

/* Packet types (type depends on payload) */
enum {
	PACKET_TYPE_DEBUG,
	PACKET_TYPE_MOTION,

	PACKET_TYPE_COUNT
};

/* 16-bytes, motion data */
struct payload_motion {
	float x;
	float y;
	float z;
	float a;
};

/* 4-byte, debug data */
struct payload_debug {
	uint8_t led_on;
	uint8_t reserved[3];
};

/*
 * 32-byte control packets
 *
 * +-----------------------------+--------------------+------------------------+
 * |       header (4 bytes)      | payload (24 bytes) |     tail (4 bytes)     |
 * +------+---------+-----+------+--------------------+-----+-----+-----+------+
 * | 0xFF | address | dir | type |   ~~~~ data ~~~~   | flags(2x) | crc | 0xFF |
 * +------+---------+-----+------+--------------------+-----+-----+-----+------+
 *
 * off
 *  0: 0xFF	- packet start token
 *  1: address	- destination node address (PC is 0)
 *  2: dir	- direction to (0x22) or from (0x44) the host
 *  3: type	- type of payload
 *  4: data	- actual payload (16 bytes always, see above)
 * 28: flags	- 16 bit flags (reserved)
 * 30: crc	- crc7 of the packet
 * 31: 0xFF	- packet end token
 */

#define PACKET_SIZE	32

struct packet {
	uint8_t start;
	uint8_t address;
	uint8_t dir;
	uint8_t type;

	/* Always 24-bytes */
	union {
		struct payload_debug as_debug;
		struct payload_motion as_motion;
		uint8_t as_bytes[24];
	};

	uint16_t flags;
	uint8_t crc;
	uint8_t end;
};

typedef bool (*packet_handler_t)(struct packet*);

void control_init(void);

#endif

