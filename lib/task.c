#include <stdlib.h>

#include "task.h"
#include "stack.h"

/*
 * Initialize a task.
 * Arguments:
 *     void (*entry)() - Pointer to a function to run.
 * Returns:
 *     task_t * - New task.
 */
task_t *init_task(void (*entry)()) {
    // Create the new task
    task_t *task = (task_t *)malloc(sizeof(task_t));
    if(!task) return NULL;
    
    task->stack = alloc_stack();
    if(!task->stack) {
        free(task);
        return NULL;
    }

    task->entry = entry;
    task->state = Ready;

    // Initialize the task stack
    init_stack(task);

    return task;
}

/*
 * Free a task.
 * Arguments:
 *     task_t *task - Self reference.
 */
void free_task(task_t *task) {
    if(task) {
        if(task->stack) {
            free_stack(task->stack);
        }
        free(task);
    }
}