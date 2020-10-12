/*
 * Part of the Conic project - robot arm controller
 *
 * Arm motion controller. 5 servos arm, and claw
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <string.h> /* for memset */
#include <stdlib.h> /* for abs */
#include <math.h>
#include <core/arm.h>
#include <core/serial.h>
#include <core/tasks.h>
#include <board/common.h>
#include <drivers/servo.h>
#include <misc/stuff.h>
#include <misc/linmath.h>
#include <misc/endian.h>
#include <proto/messages.h>

#define AXIS_COUNT	6

struct axis {
	int16_t start, end, delta;
	int16_t value, error, sign;
	struct servo servo;
};

struct motion {
	struct axis *driving_axis;
	struct axis axes[AXIS_COUNT];
};

/* settings are in mm */
static vec3 current_position = mkvec3(100, 0, 0);
static struct motion motion_logic;
static struct task motion_tick_task;
static struct serial_handler move_packet_handler;

static void motion_update(struct motion *m)
{
	struct axis *a;

	for (int i = 0; i < AXIS_COUNT; i++) {
		a = &(m->axes[i]);

		servo_set(&a->servo, a->value);

		if (a->value != a->end) {
			a->error += a->delta;
			if (2 * a->error >= m->driving_axis->delta) {
				a->value += a->sign;
				a->error -= m->driving_axis->delta;
			}
		}
	}
}

static void motion_execute(struct motion *m)
{
	struct axis *a;
	int max_index;
	int16_t max_delta = -1;

	for (int i = 0; i < AXIS_COUNT; i++) {
		a = &(m->axes[i]);

		a->delta = abs(a->end - a->start);
		a->value = a->start;
		a->error = 0;
		a->sign = (a->end > a->start)? 1 : -1;

		if (a->delta > max_delta) {
			max_delta = a->delta;
			max_index = i;
		}
	}

	m->driving_axis = &(m->axes[max_index]);
}

/*
 * For now all the calculation is hardcoded here for our specific
 * robot configuration.
 */
static void point_calculate(vec3 point, float angles[static AXIS_COUNT])
{
	float rp, rf;

	rp = sqrtf(point.x * point.x + point.y * point.y);
	rf = sqrtf(point.x * point.x + point.y * point.y + point.z * point.z);

	angles[0] = M_PI;
	angles[1] = 0;
	angles[2] = M_PI;
	angles[3] = 0;
	angles[4] = 0;
	angles[5] = M_PI;//asinf(point.y / rp);
}

/* This is very servo-dependent... */
static inline uint16_t angle_to_pulse(float angle)
{
	/* approx 400 - 2400 */
	return 636.6f * angle + 400.f;
}

/*
 * It's totally redundant to re-calculate both points every time here,
 * yet we do it here. Better save angles somewhere and use them rather then
 * re-creating last point every time
 */
static void motion_calculate(struct motion *m, vec3 start, vec3 end)
{
	float angles_end[AXIS_COUNT];
	float angles_start[AXIS_COUNT];

	point_calculate(end, angles_end);
	point_calculate(start, angles_start);

	for (int i = 0;  i < AXIS_COUNT; i++) {
		m->axes[i].end = angle_to_pulse(angles_end[i]);
		m->axes[i].start = angle_to_pulse(angles_start[i]);
	}
}

static void move_from_current(struct motion *m, vec3 target_position)
{
	motion_calculate(m, current_position, target_position);
	motion_execute(m);

	/* TODO: We should update target position in realtime, really */
	current_position = target_position;
}

static void move_callback(void *raw_data)
{
	struct move_packet_payload *payload;

	payload = raw_data;
	payload->x = le16_to_cpu(payload->x);
	payload->y = le16_to_cpu(payload->y);
	payload->z = le16_to_cpu(payload->z);

	move_from_current(&motion_logic, \
			mkvec3(payload->x, payload->y, payload->z));
}

static void motion_tick(void)
{
	/* TODO: We can calculate acceleration and update it here */
	motion_update(&motion_logic);
}

void arm_init(void)
{
	struct axis *axes = motion_logic.axes;

	servo_init(&axes[0].servo, BOARD_SERVO_1_PORT, BOARD_SERVO_1_PIN);
	servo_init(&axes[1].servo, BOARD_SERVO_2_PORT, BOARD_SERVO_2_PIN);
	servo_init(&axes[2].servo, BOARD_SERVO_3_PORT, BOARD_SERVO_3_PIN);
	servo_init(&axes[3].servo, BOARD_SERVO_4_PORT, BOARD_SERVO_4_PIN);
	servo_init(&axes[4].servo, BOARD_SERVO_5_PORT, BOARD_SERVO_5_PIN);
	servo_init(&axes[5].servo, BOARD_SERVO_6_PORT, BOARD_SERVO_6_PIN);

	/* Make a dummy move to initialize everything */
	move_from_current(&motion_logic, mkvec3(-150, 0, 0));

	serial_handle(&move_packet_handler, MOVE_PACKET_ID, move_callback);
	task_init(&motion_tick_task, motion_tick, 100);
}

