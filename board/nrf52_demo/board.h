/*
 * Part of the Conic project - robot arm controller
 *
 * NRF52 demo board support
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef BOARD_NRF52_DEMO_H
#define BOARD_NRF52_DEMO_H

#define BOARD_LED_PORT		NRF_P0
#define BOARD_LED_PIN		8

/* UART */
#define BOARD_UART_TX_PIN	20
#define BOARD_UART_RX_PIN	19

/* Servos (some random pins, since we do not have nrf52 boards yet) */
#define BOARD_SERVO_1_PORT	NRF_P0
#define BOARD_SERVO_2_PORT	NRF_P0
#define BOARD_SERVO_3_PORT	NRF_P0
#define BOARD_SERVO_4_PORT	NRF_P0
#define BOARD_SERVO_5_PORT	NRF_P0
#define BOARD_SERVO_6_PORT	NRF_P0

#define BOARD_SERVO_1_PIN	0
#define BOARD_SERVO_2_PIN	1
#define BOARD_SERVO_3_PIN	2
#define BOARD_SERVO_4_PIN	3
#define BOARD_SERVO_5_PIN	4
#define BOARD_SERVO_6_PIN	5

#endif

