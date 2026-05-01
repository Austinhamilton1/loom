#include <stdlib.h>

#include "loom.h"
#include "task.h"
#include "stack.h"
#include "scheduler.h"
#include "context.h"

static scheduler_t *global_scheduler = NULL;

/*
 * Initialize the loom environment.
 */
void loom_init() {
    global_scheduler = init_scheduler();
}

/* 
 * Cleanup the loom environment.
 */
void loom_deinit() {
    free_scheduler(global_scheduler);
}

/*
 * Spawn a new task in the loom environment.
 * Arguments:
 *     void (*entry)() - Pointer to a function to use as entry point for new task.
 */
void loom_spawn(void (*entry)()) {
    if(global_scheduler) {
        // Create the new task
        task_t *task = init_task(entry);
        if(task) {
            // Spawn the task into the scheduler
            scheduler_spawn(global_scheduler, task);
        }
    }
}

/*
 * Start running the loom environment.
 */
void loom_run() {
    if(global_scheduler) {
        scheduler_run(global_scheduler);
    }
}

/*
 * Yield control to the loom environment.
 */
void loom_yield() {
    if(global_scheduler) {
        scheduler_yield(global_scheduler);
    }
}

/*
 * Exit from a task.
 */
void loom_exit() {
    if(!global_scheduler) return;

    scheduler_exit(global_scheduler);
}

/*
 * Trampoline function (acts as an entry point for new Tasks).
 */
void trampoline() {
    if(!global_scheduler || !global_scheduler->current) {
        return;
    }

    task_t *task = global_scheduler->current;

    task->entry();
    task->state = Done;

    scheduler_yield(global_scheduler);
}