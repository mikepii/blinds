#ifndef BLINDS_MOTOR_INCLUDE_BLINDS_MOTOR_POSITION_H_
#define BLINDS_MOTOR_INCLUDE_BLINDS_MOTOR_POSITION_H_

#include <blinds/util/configure.h>
#include <limits.h>
#include <stddef.h>
#define BLINDS_RPM_LEVEL_UNSET -1

enum blinds_motor_dir_t { stopped, forward, backward };
typedef long blinds_motor_position_t;
#define BLINDS_MOTOR_POS_MIN LONG_MIN
#define BLINDS_MOTOR_POS_MAX LONG_MAX
typedef void blinds_motor_pos_cb_t(blinds_motor_position_t);

typedef struct {
  unsigned time_micros;
  blinds_motor_position_t position;
  unsigned time_created_micros;
} position_milestone_t;

typedef struct {
  enum blinds_motor_dir_t direction;
  blinds_motor_position_t position;
  blinds_motor_position_t target;
  blinds_motor_pos_cb_t *completion_cb;
  int rpm0_level_prev;
  position_milestone_t milestones[BLINDS_RPM_WATCH_EVENTS_SZ];
  size_t milestones_n;
  size_t milestone_prev_i;
} blinds_motor_pos_state_t;
blinds_motor_pos_state_t *blinds_motor_pos_state_create();
void blinds_motor_pos_state_free(blinds_motor_pos_state_t *state);

void blinds_motor_pos_step(blinds_motor_pos_state_t *state);
void blinds_motor_pos_start(blinds_motor_pos_state_t *state, blinds_motor_position_t target,
                            blinds_motor_pos_cb_t *);
void blinds_motor_pos_stop(blinds_motor_pos_state_t *);

#endif //BLINDS_MOTOR_INCLUDE_BLINDS_MOTOR_POSITION_H_
