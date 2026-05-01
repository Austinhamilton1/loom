#ifndef STACK_H
#define STACK_H

#include <stddef.h>

#include "task.h"

#define STACK_SIZE 64 * 1024

/*
 * Allocate a stack.
 * Returns:
 *     char * - Stack data.
 */
char *alloc_stack();

/*
 * Free a stack.
 * Arguments:
 *     char *stack - Self reference.
 */
void free_stack(char *stack);

/*
 * Initialize a task's stack for the first call.
 * Arguments:
 *     task_t *task - Task to initialize.
 */
void init_stack(task_t *task);

#endif