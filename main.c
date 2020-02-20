#include <blinds/concurrency/concurrency.h>
#include <blinds/hdw/hdw.h>
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
      blinds_hdw_forward();
    }
    else {
      state->dir = 0;
      blinds_hdw_backward();
    }
    state->dir_time_ms = now;
  }
}

static task_t *create_demo() {
  task_t *demo = blinds_conc_alloc_task();
  demo->interval = 1;
  demo->state = alloc_state_demo();
  demo->destroy_state = (void (*)(void *)) &destroy_state_demo;
  demo->fn = (void (*)(void *)) &demo_fn;
  return demo;
}

int main() {
  blinds_hdw_init();
  event_loop_t *event_loop = blinds_conc_alloc_event_loop(10);
  event_loop->tasks[0] = create_demo();
  event_loop->tasks_n++;
  printf("Hello, World (event loop)\n");
  blinds_conc_run_loop(event_loop);
  blinds_conc_destroy_event_loop(event_loop);
  return 0;
}
