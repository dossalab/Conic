/*
 * Part of the Conic project - robot arm controller
 *
 * Endian conversion for network layer
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef MISC_ENDIAN_H
#define MISC_ENDIAN_H

#include <stdint.h>

union u32_bytes {
	uint32_t u32;
	uint8_t bytes[4];
};

#define swap_endian_u32(x) ( \
	((x >> 24) & 0x000000FF) | \
	((x >>  8) & 0x0000FF00) | \
	((x <<  8) & 0x00FF0000) | \
	((x << 24) & 0xFF000000) \
)

#define swap_endian_u16(x) \
	(x << 8) | (x >> 8)

#if defined(ARCH_LITTLE_ENDIAN)
	#define cpu_to_le16(x) x
	#define cpu_to_le32(x) x
	#define cpu_to_be16(x) swap_endian_u16(x)
	#define cpu_to_be32(x) swap_endian_u32(x)

	#define le16_to_cpu(x) x
	#define le32_to_cpu(x) x
	#define be16_to_cpu(x) swap_endian_u16(x)
	#define be32_to_cpu(x) swap_endian_u32(x)

#elif defined(ARCH_BIG_ENDIAN)
	#define cpu_to_le16(x) swap_endian_u16(x)
	#define cpu_to_le32(x) swap_endian_u32(x)
	#define cpu_to_be16(x) x
	#define cpu_to_be32(x) x

	#define le16_to_cpu(x) swap_endian_u16(x)
	#define le32_to_cpu(x) swap_endian_u32(x)
	#define be16_to_cpu(x) x
	#define be32_to_cpu(x) x
#else
	#error Arch endiannes is undefined!
#endif

#endif

