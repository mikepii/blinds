#include "blinds/concurrency/concurrency.h"
#include <stdlib.h>

task_t *blinds_conc_alloc_task() {
  task_t *task = malloc(sizeof(task_t));
  task->state = 0;
  task->destroy_state = 0;
  task->interval = 0;
  task->fn = 0;
  return task;
}

void blinds_conc_destroy_task(task_t *task) {
  task->destroy_state(task->state);
  free(task);
}

event_loop_t *blinds_conc_alloc_event_loop(int tasks_sz) {
  event_loop_t *event_loop = malloc(sizeof(event_loop_t));
  event_loop->tasks = calloc(tasks_sz, sizeof(task_t));
  event_loop->tasks_n = 0;
  return event_loop;
}

void blinds_conc_destroy_event_loop(event_loop_t *event_loop) {
  for (int i = 0; i < event_loop->tasks_n; ++i) {
    blinds_conc_destroy_task(event_loop->tasks[i]);
  }
  free(event_loop->tasks);
  free(event_loop);
}

void blinds_conc_run_loop(event_loop_t *event_loop) {
  unsigned int loop_num = 0;
  int i;
  while (1) {
    ++loop_num;
    for (i = 0; i < event_loop->tasks_n; ++i) {
      if (loop_num % event_loop->tasks[i]->interval == 0) {
        event_loop->tasks[i]->fn(event_loop->tasks[i]->state);
      }
    }
  }
}
