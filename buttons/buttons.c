/**
 * @file buttons/buttons.c
 * @brief "Buttons" controller implementation.
 *
 * Controls the Buttons IO layer and the Motor Position layer.
 */

#include "blinds/buttons/buttons.h"
#include <blinds/buttons/io/io.h>
#include <blinds/motor/position.h>
#include <blinds/util/logging.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Allocates "Buttons" controller.
 * @see blinds_buttons_state_free()
 * @param motor_pos_state
 * @return "Buttons" controller (caller owns it)
 */
blinds_buttons_state_t *blinds_buttons_state_create(blinds_motor_pos_state_t *const motor_pos_state) {
  blinds_buttons_state_t *state = malloc(sizeof(blinds_buttons_state_t));
  state->motor_pos_state = motor_pos_state;
  state->btn_backward_prev = false;
  state->btn_forward_prev = false;
  return state;
}

/**
 * @brief Frees "Buttons" controller.
 * @see blinds_conc_task_create()
 */
void blinds_buttons_state_free(blinds_buttons_state_t *state) {
  free(state);
}

/**
 * @brief "Buttons" controller event loop hook.
 * @see blinds_conc_task_create()
 */
void blinds_buttons_step(blinds_buttons_state_t *const state) {
  const bool forward = blinds_buttons_read_forward();
  const bool backward = blinds_buttons_read_backward();
  const bool either = forward || backward;
  const bool either_prev = state->btn_backward_prev || state->btn_forward_prev;
  if (either_prev && !either) {
    logmsg(info, "buttons", "buttons released");
    blinds_motor_pos_stop(state->motor_pos_state);
  } else if (forward && !state->btn_forward_prev) {
    logmsg(info, "buttons", "forward pressed");
    blinds_motor_pos_start(state->motor_pos_state, BLINDS_MOTOR_POS_MAX, NULL);
  } else if (backward && !state->btn_backward_prev) {
    logmsg(info, "buttons", "backward pressed");
    blinds_motor_pos_start(state->motor_pos_state, BLINDS_MOTOR_POS_MIN, NULL);
  }
  state->btn_forward_prev = forward;
  state->btn_backward_prev = backward;
}
