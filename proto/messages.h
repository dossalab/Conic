/*
 * Part of the Conic project - robot arm controller
 *
 * All of the messages between host and firmware
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef PROTO_MESSAGES_H
#define PROTO_MESSAGES_H

#define MOVE_PACKET_ID		0x11

struct move_packet_payload {
	int16_t x;
	int16_t y;
	int16_t z;
};

#endif

