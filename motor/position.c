/**
 * @file motor/position.c
 * @brief "Motor position" implementation.
 *
 * Controls the Motor IO layer.
 * Controlled by the Buttons layer and the (future) Samsung SmartThings layer.
 */

#include "blinds/motor/position.h"
#include <blinds/motor/io/io.h>
#include <stdlib.h>
#include <blinds/util/configure.h>
#include <blinds/util/logging.h>
#include <blinds/util/time.h>

/**
 * @brief Allocates "motor position" state.
 * @see blinds_motor_pos_state_free()
 * @see blinds_conc_task_create()
 * @return "Motor position" state (caller owns it)
 */
blinds_motor_pos_state_t *blinds_motor_pos_state_create() {
  blinds_motor_pos_state_t *state = malloc(sizeof(blinds_motor_pos_state_t));
  state->direction = stopped;
  state->completion_cb = NULL;
  state->position = 0;
  state->target = 0;
  state->rpm0_level_prev = BLINDS_RPM_LEVEL_UNSET;
  state->milestones_n = 0;
  state->milestone_prev_i = -1;
  state->rpmlog_direction_prev = stopped;
  state->rpmlog_micros_start = 0;
  state->rpmlog_position_start = 0;
  return state;
}

/**
 * @brief Frees "motor position" state.
 * @see blinds_motor_pos_state_create()
 * @see blinds_conc_task_create()
 */
void blinds_motor_pos_state_free(blinds_motor_pos_state_t * state) {
  free(state);
}

/**
 * @brief Instructs "motor position" to stop moving the motor.
 */
void blinds_motor_pos_stop(blinds_motor_pos_state_t *const state) {
  blinds_motor_io_stop();
  state->direction = stopped;
  if (state->completion_cb != NULL) {
    state->completion_cb(state->position);
  }
}

/**
 * @brief Updates \c state->position based on motor encoder sensor level.
 * @see @def BLINDS_MOTOR_EV_PER_ROTATION
 */
static void update_position(blinds_motor_pos_state_t *const state) {
  const int rpm0_level = blinds_motor_io_read_rpm0();
  if (state->rpm0_level_prev == 0 && rpm0_level == 1) {
    state->position += state->direction == forward ? 1 : -1;
  }
  state->rpm0_level_prev = rpm0_level;
}

/**
 * @brief Logs motor speed (e.g. to syslog).
 */
static void log_rpm(blinds_motor_pos_state_t *const state, const micros_t now) {
  const bool moving = state->direction != stopped;
  const bool started_moving = moving && state->rpmlog_direction_prev == stopped;
  const bool stopped_moving = !moving && state->rpmlog_direction_prev != stopped;
  const bool continued_moving = !started_moving && moving;
  const bool changed_direction = continued_moving && state->rpmlog_direction_prev != state->direction;
  const micros_t interval_micros = now - state->rpmlog_micros_start;
  const bool interval_elapsed = continued_moving && (interval_micros > BLINDS_RPM_LOG_INTERVAL_S * 1000 * 1000);
  // Log RPM
  if (changed_direction || interval_elapsed || stopped_moving) {
    const double rotations =
        (double) (state->position - state->rpmlog_position_start) / BLINDS_MOTOR_EV_PER_ROTATION;
    const double rpm = rotations / (interval_micros / 1000.0 / 1000.0) * 60;
    logmsg(info, "motor", "RPM=%f", rpm);
  }
  // Set/reset RPM monitoring start
  if (changed_direction || interval_elapsed || started_moving) {
    state->rpmlog_position_start = state->position;
    state->rpmlog_micros_start = now;
  }
  // Update direction
  state->rpmlog_direction_prev = state->direction;
}

/**
 * @brief Checks whether motor has reached all current milestones.
 * @see add_milestone()
 * @return @c true if the motor has reached all current milestones.
 */
static bool check_milestones(blinds_motor_pos_state_t *const state, const micros_t now) {
  for (size_t i = 0; i < state->milestones_n; i++) {
    // Assumes we're running the motor for less than micros() wrap time (~71 min)
    if (state->milestones[i].time_micros < now && (
        (state->direction == forward && state->position < state->milestones[i].position) ||
        (state->direction == backward && state->position > state->milestones[i].position)
        )) {
      return false;
    }
  }
  return true;
}

/**
 * @brief Adds a milestone if it's time to do so.
 *
 * Milestones are added at an interval defined by \def BLINDS_MILESTONE_INTERVAL_MICROS.
 *
 * @see check_milestones()
 */
static void add_milestone(blinds_motor_pos_state_t *const state, const micros_t now) {
  // Limit milestones by interval
  if (state->milestones_n > 0 &&
      now < state->milestones[state->milestone_prev_i].time_created_micros + BLINDS_MILESTONE_INTERVAL_MICROS) {
    return;
  }
  // Calculate milestone
  const size_t idx = state->milestones_n == 0 ? 0 : (state->milestone_prev_i + 1) % BLINDS_RPM_WATCH_EVENTS_SZ;
  state->milestones[idx].time_created_micros = now;
  state->milestones[idx].time_micros = now + BLINDS_MILESTONE_HORIZON_MICROS;
  const double events_expected =
      (double) BLINDS_MOTOR_EV_PER_ROTATION * BLINDS_MOTOR_TARGET_RPM / 60 / 1000000 * BLINDS_MILESTONE_HORIZON_MICROS;
  if (state->direction == forward) {
    const blinds_motor_position_t events_required_fwd =
        events_expected - BLINDS_RPM_WATCH_ALLOWED_ERR_PCT100_FWD / 100.0 * events_expected;
    state->milestones[idx].position = state->position + events_required_fwd;
  } else {
    const blinds_motor_position_t events_required_bwd =
        events_expected - BLINDS_RPM_WATCH_ALLOWED_ERR_PCT100_BWD / 100.0 * events_expected;
    state->milestones[idx].position = state->position - events_required_bwd;
  }
  if (state->milestones_n < BLINDS_RPM_WATCH_EVENTS_SZ) {
    state->milestones_n += 1;
  }
  state->milestone_prev_i = idx;
}

/**
 * @brief "Motor position" event loop hook.
 * @see blinds_conc_task_create()
 */
void blinds_motor_pos_step(blinds_motor_pos_state_t *const state) {
  // Use the same "now" in all places using the same position read.
  const micros_t now = micros();
  if (state->direction != stopped) {
    update_position(state);
    if (check_milestones(state, now)) {
      add_milestone(state, now);
    } else {
      blinds_motor_pos_stop(state);
    }
  }
  log_rpm(state, now);
}

/**
 * @brief Instructs "motor position" to move the motor to a particular position.
 */
void blinds_motor_pos_start(blinds_motor_pos_state_t *const state, const blinds_motor_position_t target,
                            blinds_motor_pos_cb_t *const cb) {
  state->target = target;
  state->completion_cb = cb;
  state->milestones_n = 0;
  state->milestone_prev_i = -1;
  if (target < state->position) {
    state->direction = backward;
    blinds_motor_io_backward();
  } else {
    state->direction = forward;
    blinds_motor_io_forward();
  }
}
