#include <blinds/concurrency/eventloop.h>
#include <blinds/motor/position.h>
#include <blinds/motor/io/io.h>
#include <limits.h>
#include <stdio.h>

static void motor_done(blinds_motor_position_t position) {
  printf("done. position=%ld\n", position);
}

int main() {
  blinds_motor_io_init();
  event_loop_t *event_loop = blinds_conc_event_loop_create(10);

  blinds_motor_pos_state_t *motor_drive_state = blinds_motor_pos_state_create();
  task_t *motor_drive_task = blinds_conc_task_create(motor_drive_state, 1,
                                                     (void (*)(void *)) &blinds_motor_pos_step,
                                                     (void (*)(void *)) &blinds_motor_pos_state_free);
  blinds_conc_event_loop_add_task(event_loop, motor_drive_task);

  blinds_motor_pos_start(motor_drive_state, LONG_MAX, &motor_done);

  printf("Hello, World (motor drive impl)\n");
  blinds_conc_run_loop(event_loop);
  blinds_conc_event_loop_free(event_loop);
  return 0;
}
