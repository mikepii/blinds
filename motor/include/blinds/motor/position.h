/**
 * @file motor/position.h
 * @brief "Motor position" object definitions.
 */

#ifndef BLINDS_MOTOR_INCLUDE_BLINDS_MOTOR_POSITION_H_
#define BLINDS_MOTOR_INCLUDE_BLINDS_MOTOR_POSITION_H_

#include <blinds/util/configure.h>
#include <blinds/util/time.h>
#include <limits.h>
#include <stddef.h>

#define BLINDS_RPM_LEVEL_UNSET -1

/**
 * @brief Motor direction or stopped
 */
enum blinds_motor_dir_t { stopped, forward, backward };

/**
 * @brief Motor position as measured by sensor events in either direction since program start.
 */
typedef long blinds_motor_position_t;
#define BLINDS_MOTOR_POS_MIN LONG_MIN
#define BLINDS_MOTOR_POS_MAX LONG_MAX

/**
 * @brief Callback for motor position change completion (reached target or stopped for another reason).
 *
 * Takes as an argument the final position.
 */
typedef void blinds_motor_pos_cb_t(blinds_motor_position_t);

/**
 * @brief A position that the motor is expected to reach at a particular time under normal load.
 *
 * Used for detecting high load on the moter (tension on the blinds pull cord => reached the end).
 */
typedef struct {
  micros_t time_micros;
  blinds_motor_position_t position;
  micros_t time_created_micros;
} position_milestone_t;

/**
 * @brief State for "motor position".
 * @see blinds_motor_pos_state_create()
 * @see blinds_motor_pos_state_free()
 */
typedef struct {
  enum blinds_motor_dir_t direction;
  blinds_motor_position_t position;
  blinds_motor_position_t target;
  blinds_motor_pos_cb_t *completion_cb;
  int rpm0_level_prev;
  position_milestone_t milestones[BLINDS_RPM_WATCH_EVENTS_SZ];
  size_t milestones_n;
  size_t milestone_prev_i;
  enum blinds_motor_dir_t rpmlog_direction_prev;
  blinds_motor_position_t rpmlog_position_start;
  micros_t rpmlog_micros_start;
} blinds_motor_pos_state_t;

/**
 * @brief Allocates "motor position" state.
 * @see blinds_motor_pos_state_free()
 * @see blinds_conc_task_create()
 * @return "Motor position" state (caller owns it)
 */
blinds_motor_pos_state_t *blinds_motor_pos_state_create();

/**
 * @brief Frees "motor position" state.
 * @see blinds_motor_pos_state_create()
 * @see blinds_conc_task_create()
 */
void blinds_motor_pos_state_free(blinds_motor_pos_state_t *state);

/**
 * @brief "Motor position" event loop hook.
 */
void blinds_motor_pos_step(blinds_motor_pos_state_t *state);

/**
 * @brief Instructs "motor position" to move the motor to a particular position.
 */
void blinds_motor_pos_start(blinds_motor_pos_state_t *state, blinds_motor_position_t target,
                            blinds_motor_pos_cb_t *);

/**
 * @brief Instructs "motor position" to stop moving the motor.
 */
void blinds_motor_pos_stop(blinds_motor_pos_state_t *);

#endif //BLINDS_MOTOR_INCLUDE_BLINDS_MOTOR_POSITION_H_
