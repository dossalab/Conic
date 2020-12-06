/*
 * Part of the Conic project - robot arm controller
 *
 * This library should provide a link between high-level application
 * (might be for robotics, toys, home appliances, stuff like that) and device
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef LIBCONIC_H
#define LIBCONIC_H

#ifdef _WIN32
	#define API_EXPORT __declspec(dllexport)
#else
	#define API_EXPORT
#endif

#include <errno.h>
#include <stdint.h>

#define CONIC_BAUDRATE	115200

/*
 * Create and initialize a servo
 *
 * args:
 *   handle - handle of the connected device
 *   port   - gpio port that used for data signal (just letter, like 'A')
 *   pin    - gpio pin for data signal
 *
 * return: servo handle; negative value in case of an error
 */
int API_EXPORT conic_servo_init(int handle, char port, int8_t pin);

/*
 * Set servo position. Notice that this will only set it virtually; to actually
 * start motion use conic_execute_motion
 *
 * args:
 *   handle - handle of the connected device
 *   servo  - handle of servo
 *   pulse  - duration of servo pulse in microseconds.
 *
 * return: 0 on success; negative value in case of an error
 */
int API_EXPORT conic_servo_move(int handle, uint8_t servo, uint16_t pulse);

/*
 * Execute motion. If there is any servo set before this call, start moving it
 * at constant rate. Any other servos are not affected.
 *
 * args:
 *   handle - handle of the connected device
 *
 * return: 0 on success; negative value in case of an error
 */
int API_EXPORT conic_execute_motion(int handle);

/*
 * Just checks if device is connected or not
 *
 * args:
 *   handle - handle of the connected device
 *
 * return: 0 on success; negative value in case of an error
 */
int API_EXPORT conic_check_presense(int handle);

/*
 * Lookup port and open a connection to the device.
 *
 * args: nope
 * return: opened device handle; negative value in case of an error
 */
int API_EXPORT conic_device_open(void);

/*
 * Close connection.
 *
 * args:
 *   handle - handle of the connected device
 *
 * return: nope
 */
void API_EXPORT conic_device_close(int handle);

#endif

