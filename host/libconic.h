/*
 * Part of the Conic project - robot arm controller
 *
 * libconic - PC interfacing library
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef LIBCONIC_H
#define LIBCONIC_H

#include <stdint.h>

#ifdef _WIN32
  #define API_EXPORT __declspec(dllexport)
#else
  #define API_EXPORT
#endif

/* TODO: provide a configuration option for that */
#define ARCH_LITTLE_ENDIAN
#define CONIC_BAUDRATE	115200

int API_EXPORT conic_open(void);
int API_EXPORT conic_is_open(int fd);
int API_EXPORT conic_move(int fd, int16_t s1, int16_t s2, int16_t s3,
			int16_t s4, int16_t s5, int16_t s6);
void API_EXPORT conic_close(int fd);

#endif

