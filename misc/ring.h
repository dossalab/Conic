/*
 * Part of the Conic project - robot arm controller
 *
 * Simple ring buffer.
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef MISC_RING_H
#define MISC_RING_H

#include <stdint.h>
#include <stddef.h>

struct ring {
	uint8_t in;
	uint8_t mask;
	uint8_t *data;
};

/* size must be power of two */
#define DECLARE_RING(name, size) \
	uint8_t __##name##_buffer[size]; \
	struct ring name = { \
		.in = 0, \
		.mask = size - 1, \
		.data = __##name##_buffer \
	};

/*
 * & here works as modulo operator but 10 times faster
 * (only applicable for array of power of two size)
 */
static inline void ring_push(struct ring *r, uint8_t value)
{
	r->data[r->in++] = value;
	r->in &= r->mask;
}

static inline uint8_t ring_start(struct ring *r)
{
	return r->data[r->in];
}

static inline uint8_t ring_end(struct ring *r)
{
	return r->data[(r->in + r->mask) & r->mask];
}

static inline void ring_copy(struct ring *r, uint8_t *buffer, size_t len)
{
	uint8_t in = r->in;

	while (len--) {
		*buffer++ = r->data[(in++) & r->mask];
	}
}

#endif

