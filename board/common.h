/*
 * Part of the Conic project - robot arm controller
 *
 * Generic board api. Implementation goes into board/<board-name>
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include BOARD_SPECIFIC_HEADER

#ifndef BOARD_COMMON_H
#define BOARD_COMMON_H

void board_init(void);

#endif

