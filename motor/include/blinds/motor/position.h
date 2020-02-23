#ifndef BLINDS_MOTOR_INCLUDE_BLINDS_MOTOR_POSITION_H_
#define BLINDS_MOTOR_INCLUDE_BLINDS_MOTOR_POSITION_H_

#include <stddef.h>
#define BLINDS_RPM_LEVEL_UNSET -1
#define BLINDS_RPM_WATCH_EVENTS_SZ 100
#define BLINDS_RPM_WATCH_ALLOWED_ERR_PCT 7.0

enum blinds_motor_dir_t { stopped, forward, backward };
typedef long blinds_motor_position_t;
typedef void blinds_motor_pos_cb_t(blinds_motor_position_t);

typedef struct {
  unsigned time_micros;
  int position;
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

#endif //BLINDS_MOTOR_INCLUDE_BLINDS_MOTOR_POSITION_H_