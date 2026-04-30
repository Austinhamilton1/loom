#include <stdlib.h>

#include "loom.h"
#include "task.h"
#include "stack.h"

/*
 * Initialize the loom environment.
 */
void loom_init() {
    global_scheduler = init_scheduler();
}

/*
 * Spawn a new task in the loom environment.
 * Arguments:
 *     void (*entry)() - Pointer to a function to use as entry point for new task.
 */
void loom_spawn(void (*entry)()) {
    if(global_scheduler) {
        // Create the new task
        task_t *task = (task_t *)malloc(sizeof(task_t));
        task->stack = alloc_stack();
        task->entry = entry;
        task->state = Ready;

        // Initialize the task stack
        init_stack(task);

        // Spawn the task into the scheduler
        scheduler_spawn(global_scheduler, task);
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
 * Trampoline function (acts as an entry point for new Tasks).
 */
void trampoline() {
    if(global_scheduler) {
        if(global_scheduler->current) {
            task_t *task = global_scheduler->current;
            task->entry();
            task->state = Done;

            while(1) {
                loom_yield();
            }
        }
    }
}