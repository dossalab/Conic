/*
 * Part of the Conic project - robot arm controller
 *
 * libconic - PC interfacing library
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <proto/serial.h>

#ifdef __MINGW32__
  #define API_EXPORT __declspec(dllexport)
#else
  #define API_EXPORT
#endif

void API_EXPORT conic_init(void)
{

}

