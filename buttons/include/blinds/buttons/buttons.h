#ifndef BLINDS_BUTTONS_INCLUDE_BLINDS_BUTTONS_BUTTONS_H_
#define BLINDS_BUTTONS_INCLUDE_BLINDS_BUTTONS_BUTTONS_H_

#include "blinds/buttons/buttons.h"
#include <blinds/motor/position.h>
#include <stdbool.h>

typedef struct {
  blinds_motor_pos_state_t *motor_pos_state;
  bool btn_forward_prev;
  bool btn_backward_prev;
} blinds_buttons_state_t;
blinds_buttons_state_t *blinds_buttons_state_create(blinds_motor_pos_state_t *);
void blinds_buttons_state_free(blinds_buttons_state_t *);

void blinds_buttons_step(blinds_buttons_state_t *);

#endif //BLINDS_BUTTONS_INCLUDE_BLINDS_BUTTONS_BUTTONS_H_
