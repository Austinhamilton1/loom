#include <stdlib.h>

#include "scheduler.h"
#include "context.h"

/*
 * Create a scheduler.
 * Returns
 *     scheduler_t * - Pointer to the new scheduler.
 */
scheduler_t *init_scheduler() {
    scheduler_t *sched = (scheduler_t *)malloc(sizeof(scheduler_t));

    sched->current = NULL;
    sched->main_sp = 0;
    sched->run_queue = init_queue();

    return sched;
}

/*
 * Spawn a new task (add it to the run queue).
 * Arguments:
 *     scheduler_t *sched - Self reference.
 *     task_t *task - Task to spawn.
 */
void scheduler_spawn(scheduler_t *sched, task_t *task) {
    queue_push(sched->run_queue, task);
}

/*
 * Run all tasks in queue.
 * Arguments:
 *     scheduler_t *sched - Self reference.
 */
void scheduler_run(scheduler_t *sched) {
    while(sched->run_queue->size > 0) {
        task_t *next = queue_pop(sched->run_queue);
        if(next) {
            sched->current = next;
            context_switch(&sched->main_sp, next->sp);
        }
    }
}

/*
 * Yield the current task.
 * Arguments:
 *     scheduler_t *sched - Self reference.
 */
void yield(scheduler_t *sched) {
    if(sched->current) {
        queue_push(sched->run_queue, sched->current);
        context_switch(&sched->current->sp, sched->main_sp);
    }
}