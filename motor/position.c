#include "blinds/motor/position.h"
#include <blinds/motor/io/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <blinds/util/configure.h>
#include <blinds/util/util.h>

blinds_motor_pos_state_t *blinds_motor_pos_state_create() {
  blinds_motor_pos_state_t *state = malloc(sizeof(blinds_motor_pos_state_t));
  state->direction = stopped;
  state->completion_cb = NULL;
  state->position = 0;
  state->target = 0;
  state->rpm0_level_prev = BLINDS_RPM_LEVEL_UNSET;
  state->milestones_n = 0;
  state->milestone_prev_i = -1;
  return state;
}

void blinds_motor_pos_state_free(blinds_motor_pos_state_t * state) {
  free(state);
}

void blinds_motor_pos_stop(blinds_motor_pos_state_t *const state) {
  blinds_motor_io_stop();
  state->direction = stopped;
  if (state->completion_cb != NULL) {
    state->completion_cb(state->position);
  }
}

static void update_position(blinds_motor_pos_state_t *const state) {
  const int rpm0_level = blinds_motor_io_read_rpm0();
  if (state->rpm0_level_prev == 0 && rpm0_level == 1) {
    state->position += state->direction == forward ? 1 : -1;
  }
  state->rpm0_level_prev = rpm0_level;
}

static bool check_milestones(blinds_motor_pos_state_t *const state) {
//  static unsigned long aoeu = 0;
  const unsigned now = micros();
//  unsigned latest_passed_micros = 0;
//  int latest_passed_idx = -1;

  for (size_t i = 0; i < state->milestones_n; i++) {
    // Assumes we're running the motor for less than micros() wrap time (~71 min)
    if (state->milestones[i].time_micros < now && (
        (state->direction == forward && state->position < state->milestones[i].position) ||
        (state->direction == backward && state->position > state->milestones[i].position)
        )) {
//      printf("aoeu done milestones_n=%d now=%u\n", state->milestones_n, now);
      return false;
    }

//    // AOEU
//    if (state->milestones[i].time_micros <= now) {
//      if (latest_passed_idx == -1 || state->milestones[i].time_micros > latest_passed_micros) {
//        latest_passed_idx = i;
//        latest_passed_micros = state->milestones[i].time_micros;
//      }
//    }
  }

//  // AOEU
//  if (latest_passed_idx != -1 && (aoeu++ % 1000 == 0)) {
//    printf("aoeu passed latest milestone by %ld\n", state->position - state->milestones[latest_passed_idx].position);
//  }

  return true;
}

static void add_milestone(blinds_motor_pos_state_t *const state) {
  const unsigned now = micros();
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
  const blinds_motor_position_t events_required =
      events_expected - BLINDS_RPM_WATCH_ALLOWED_ERR_PCT / 100.0 * events_expected;
  if (state->direction == forward) {
    state->milestones[idx].position = state->position + events_required;
  } else {
    state->milestones[idx].position = state->position - events_required;
  }
  if (state->milestones_n < BLINDS_RPM_WATCH_EVENTS_SZ) {
    state->milestones_n += 1;
  }
  state->milestone_prev_i = idx;

//  printf("aoeu add_milestone now=%u pos=%ld ev_exp=%f ev_req=%ld milestone.pos=%d milestone.time=%u fwd=%d\n",
//      now, state->position, events_expected, events_required, state->milestones[idx].position,
//         state->milestones[idx].time_micros, state->direction == forward);
}

void blinds_motor_pos_step(blinds_motor_pos_state_t *const state) {
  if (state->direction == stopped) {
    return;
  }
  update_position(state);
  if (!check_milestones(state)) {
    blinds_motor_pos_stop(state);
    return;
  }
  add_milestone(state);
}

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
