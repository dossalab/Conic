/*
 * Part of the Conic project - robot arm controller
 *
 * Arm motion controller
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef CORE_ARM_H
#define CORE_ARM_H

#include <proto/messages.h>

void move_packet_handle(struct move_packet_payload *payload);
void arm_init(void);

#endif

