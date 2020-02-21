#include <blinds/concurrency/eventloop.h>
#include <blinds/motor/io/io.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char dir;
  unsigned int dir_time_ms;
} state_demo_t;
static state_demo_t *alloc_state_demo() {
  state_demo_t *state = malloc(sizeof(state_demo_t));
  state->dir = 0;
  state->dir_time_ms = 0;
  return state;
}
static void destroy_state_demo(state_demo_t *state) {
  free(state);
}

static void demo_fn(state_demo_t *state) {
  unsigned int now = millis();
  if (now > state->dir_time_ms + 2000) {
    if (state->dir == 0) {
      state->dir = 1;
      blinds_motor_io_forward();
    }
    else {
      state->dir = 0;
      blinds_motor_io_backward();
    }
    state->dir_time_ms = now;
  }
}

int main() {
  blinds_motor_io_init();
  event_loop_t *event_loop = blinds_conc_event_loop_create(10);
  task_t *demo_task = blinds_conc_task_create(alloc_state_demo(), 1,
      (void (*)(void *)) &demo_fn, (void (*)(void *)) &destroy_state_demo);
  blinds_conc_event_loop_add_task(event_loop, demo_task);
  printf("Hello, World (event loop)\n");
  blinds_conc_run_loop(event_loop);
  blinds_conc_event_loop_free(event_loop);
  return 0;
}
