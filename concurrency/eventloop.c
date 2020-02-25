/**
 * @file concurrency/eventloop.c
 * @brief Event loop implementation.
 */

#include "blinds/concurrency/eventloop.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

/**
 * @brief Creates a task for the event loop.
 * @param state Passed to step function (returned task takes ownership)
 * @param interval Step function will be called every N interations of the event loop
 * @param fn Task step function
 * @param state_free Used to free the step function's state
 * @return Task object (caller owns it)
 */
task_t *blinds_conc_task_create(void *state, unsigned interval, void fn(void *), void state_free(void *)) {
  task_t *task = malloc(sizeof(task_t));
  task->state = state;
  task->interval = interval;
  task->fn = fn;
  task->state_free = state_free;
  return task;
}

/**
 * @brief Frees a task and the state it was passing to the step function.
 */
void blinds_conc_task_free(task_t *task) {
  task->state_free(task->state);
  free(task);
}

/**
 * @brief Creates an event loop.
 * @param tasks_sz Task list capacity
 * @return Event loop (caller owns it)
 */
event_loop_t *blinds_conc_event_loop_create(size_t tasks_sz) {
  event_loop_t *event_loop = malloc(sizeof(event_loop_t));
  event_loop->tasks = calloc(tasks_sz, sizeof(task_t));
  event_loop->tasks_n = 0;
  event_loop->tasks_sz = tasks_sz;
  return event_loop;
}

/**
 * @brief Frees the event loop and its tasks.
 */
void blinds_conc_event_loop_free(event_loop_t *event_loop) {
  for (int i = 0; i < event_loop->tasks_n; ++i) {
    blinds_conc_task_free(event_loop->tasks[i]);
  }
  free(event_loop->tasks);
  free(event_loop);
}

/**
 * @brief Adds a task to the event loop.
 *
 * Event loop takes ownership of the task.
 *
 * @return < 0 for error
 */
int blinds_conc_event_loop_add_task(event_loop_t *event_loop, task_t *task) {
  if (event_loop->tasks_n >= event_loop->tasks_sz) {
    return -1;
  }
  event_loop->tasks[event_loop->tasks_n] = task;
  event_loop->tasks_n++;
  return 0;
}

/**
 * @brief Runs the event loop.
 */
void blinds_conc_run_loop(event_loop_t *event_loop) {
  unsigned loop_num = 0;
  size_t i;
  while (true) {
    ++loop_num;
    for (i = 0; i < event_loop->tasks_n; ++i) {
      if (loop_num % event_loop->tasks[i]->interval == 0) {
        event_loop->tasks[i]->fn(event_loop->tasks[i]->state);
      }
    }
  }
}
