#ifndef BLINDS_CONCURRENCY_INCLUDE_BLINDS_CONCURRENCY_CONCURRENCY_H_
#define BLINDS_CONCURRENCY_INCLUDE_BLINDS_CONCURRENCY_CONCURRENCY_H_

typedef struct {
  int interval;
  void (*fn)(void *state);
  void *state;
  void (*destroy_state)(void *);
} task_t;
task_t *blinds_conc_alloc_task();
void blinds_conc_destroy_task(task_t *);

typedef struct {
  task_t **tasks;
  int tasks_n;
} event_loop_t;
event_loop_t *blinds_conc_alloc_event_loop(int tasks_sz);
void blinds_conc_destroy_event_loop(event_loop_t *);

void blinds_conc_run_loop(event_loop_t *);

#endif //BLINDS_CONCURRENCY_INCLUDE_BLINDS_CONCURRENCY_CONCURRENCY_H_
