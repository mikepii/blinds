#ifndef BLINDS_CONCURRENCY_INCLUDE_BLINDS_CONCURRENCY_EVENTLOOP_H_
#define BLINDS_CONCURRENCY_INCLUDE_BLINDS_CONCURRENCY_EVENTLOOP_H_

#include <stddef.h>

typedef struct {
  void *state;
  unsigned interval;
  void (*fn)(void *state);
  void (*state_free)(void *);
} task_t;
task_t *blinds_conc_task_create(void *state, unsigned interval, void fn(void *), void state_free(void *));
void blinds_conc_task_free(task_t *);

typedef struct {
  task_t **tasks;
  size_t tasks_n;
  size_t tasks_sz;
} event_loop_t;
event_loop_t *blinds_conc_event_loop_create(size_t tasks_sz);
void blinds_conc_event_loop_free(event_loop_t *);
int blinds_conc_event_loop_add_task(event_loop_t *, task_t *);
void blinds_conc_run_loop(event_loop_t *);

#endif //BLINDS_CONCURRENCY_INCLUDE_BLINDS_CONCURRENCY_EVENTLOOP_H_
