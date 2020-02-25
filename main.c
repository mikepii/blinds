#include <blinds/buttons/buttons.h>
#include <blinds/concurrency/eventloop.h>
#include <blinds/io/io.h>
#include <blinds/motor/position.h>
#include <signal.h>
#include <stdlib.h>

static void clean_exit(const int signal) {
  blinds_io_cleanup();
  exit(signal);
}

static void init() {
  blinds_io_init();
  signal(SIGHUP, clean_exit);
  signal(SIGINT, clean_exit);
  signal(SIGQUIT, clean_exit);
}

int main() {
  init();
  event_loop_t *event_loop = blinds_conc_event_loop_create(10);
  // Motor position control
  blinds_motor_pos_state_t *motor_pos_state = blinds_motor_pos_state_create();
  task_t *motor_pos_task = blinds_conc_task_create(motor_pos_state, 1,
                                                     (void (*)(void *)) &blinds_motor_pos_step,
                                                     (void (*)(void *)) &blinds_motor_pos_state_free);
  blinds_conc_event_loop_add_task(event_loop, motor_pos_task);
  // Buttons control
  blinds_buttons_state_t *buttons_state = blinds_buttons_state_create(motor_pos_state);
  task_t *buttons_task = blinds_conc_task_create(buttons_state, 100,
                                                 (void (*)(void *)) &blinds_buttons_step,
                                                 (void (*)(void *)) &blinds_buttons_state_free);
  blinds_conc_event_loop_add_task(event_loop, buttons_task);
  // Run
  blinds_conc_run_loop(event_loop);
  blinds_conc_event_loop_free(event_loop);
  blinds_io_cleanup();
  return 0;
}
