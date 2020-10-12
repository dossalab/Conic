/*
 * Part of the Conic project - robot arm controller
 *
 * Serial packets handler
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef CORE_SERIAL_H
#define CORE_SERIAL_H

#include <stdint.h>
#include <stdbool.h>
#include <misc/list.h>
struct serial_handler {
	struct list_node node;
	uint8_t packet_type;
	void (*callback)(void *);
};

void serial_handle(struct serial_handler *h, int type, void (*callback)(void *));
void serial_system_init(void);

#endif

