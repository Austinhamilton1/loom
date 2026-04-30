#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "task.h"
#include "queue.h"

typedef struct {
    queue_t *run_queue;
    task_t *current;
    uintptr_t main_sp;
} scheduler_t;

/*
 * Create a scheduler.
 * Returns
 *     scheduler_t * - Pointer to the new scheduler.
 */
scheduler_t *init_scheduler();

/*
 * Spawn a new task (add it to the run queue).
 * Arguments:
 *     scheduler_t *sched - Self reference.
 *     task_t *task - Task to spawn.
 */
void scheduler_spawn(scheduler_t *sched, task_t *task);

/*
 * Run all tasks in queue.
 * Arguments:
 *     scheduler_t *sched - Self reference.
 */
void scheduler_run(scheduler_t *sched);

/*
 * Yield the current task.
 * Arguments:
 *     scheduler_t *sched - Self reference.
 */
void yield(scheduler_t *sched);

#endif