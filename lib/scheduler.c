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
 * Free a scheduler.
 * Arguments:
 *     scheduler_t *sched - Self reference.
 */
void free_scheduler(scheduler_t *sched) {
    if(!sched) return;

    free_task(sched->current);
    free_queue(sched->run_queue);
    free(sched);
}

/*
 * Spawn a new task (add it to the run queue).
 * Arguments:
 *     scheduler_t *sched - Self reference.
 *     task_t *task - Task to spawn.
 */
void scheduler_spawn(scheduler_t *sched, task_t *task) {
    if(!sched || !task) return;
    queue_push(sched->run_queue, task);
}

/*
 * Run all tasks in queue.
 * Arguments:
 *     scheduler_t *sched - Self reference.
 */
void scheduler_run(scheduler_t *sched) {
    if(!sched) return;
    while(sched->run_queue->size > 0) {
        task_t *next = queue_pop(sched->run_queue);
        sched->current = next;

        if(next) {
            context_switch(&sched->main_sp, next->sp);
        
            if(next->state == Done) {
                free_task(next);
                sched->current = NULL;
            } else {
                queue_push(sched->run_queue, next);
            }
        }
    }
}

/*
 * Yield the current task.
 * Arguments:
 *     scheduler_t *sched - Self reference.
 */
void scheduler_yield(scheduler_t *sched) {
    if(!sched) return;
    if(sched->current) {
        context_switch(&sched->current->sp, sched->main_sp);
    }
}

/*
 * Mark the current running task as Done.
 * Arguments:
 *     scheduler_t *sched - Self reference.
 */
void scheduler_exit(scheduler_t *sched) {
    if(!sched) return;
    if(sched->current) {
        sched->current->state = Done;
        context_switch(&sched->current->sp, sched->main_sp);
    }
}