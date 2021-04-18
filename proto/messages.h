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
	uint16_t s1;
	uint16_t s2;
	uint16_t s3;
	uint16_t s4;
	uint16_t s5;
	uint16_t s6;
};

#endif

