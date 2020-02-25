/**
 * @file concurrency/include/blinds/concurrency/eventloop.h
 * @brief Event loop interface.
 */

#ifndef BLINDS_CONCURRENCY_INCLUDE_BLINDS_CONCURRENCY_EVENTLOOP_H_
#define BLINDS_CONCURRENCY_INCLUDE_BLINDS_CONCURRENCY_EVENTLOOP_H_

#include <stddef.h>

/**
 * @brief Task for an event loop.
 * @see blinds_conc_task_create()
 * @see blinds_conc_task_free()
 */
typedef struct {
  void *state;
  unsigned interval;
  void (*fn)(void *state);
  void (*state_free)(void *);
} task_t;

/**
 * @brief Creates a task for the event loop.
 * @see blinds_conc_task_free()
 * @param state Passed to step function (returned task takes ownership)
 * @param interval Step function will be called every N interations of the event loop
 * @param fn Task step function
 * @param state_free Used to free the step function's state
 * @return Task object (caller owns it)
 */
task_t *blinds_conc_task_create(void *state, unsigned interval, void fn(void *), void state_free(void *));

/**
 * @brief Frees a task and the state it was passing to the step function.
 * @see blinds_conc_task_create()
 */
void blinds_conc_task_free(task_t *);

/**
 * @see blinds_conc_event_loop_create()
 * @see blinds_conc_event_loop_free()
 */
typedef struct {
  task_t **tasks;
  size_t tasks_n;
  size_t tasks_sz;
} event_loop_t;

/**
 * @brief Creates an event loop.
 * @see blinds_conc_event_loop_free()
 * @param tasks_sz Task list capacity
 * @return Event loop (caller owns it)
 */
event_loop_t *blinds_conc_event_loop_create(size_t tasks_sz);

/**
 * @brief Frees the event loop and its tasks.
 * @see blinds_conc_event_loop_create()
 */
void blinds_conc_event_loop_free(event_loop_t *);

/**
 * @brief Adds a task to the event loop.
 *
 * Event loop takes ownership of the task.
 *
 * @return < 0 for error
 */
int blinds_conc_event_loop_add_task(event_loop_t *, task_t *);

/**
 * @brief Runs the event loop.
 */
void blinds_conc_run_loop(event_loop_t *);

#endif //BLINDS_CONCURRENCY_INCLUDE_BLINDS_CONCURRENCY_EVENTLOOP_H_
