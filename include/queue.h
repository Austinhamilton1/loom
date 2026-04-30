#ifndef QUEUE_H
#define QUEUE_H

#include "task.h"

typedef struct {
    size_t size;
} queue_t;

/*
 * Initialize a queue.
 * Returns:
 *     queue_t * - New queue.
 */
queue_t *init_queue();

/*
 * Push a task to the queue.
 * Arguments:
 *     queue_t *queue - Self reference.
 *     task_t *task - Push this task.
 * Returns:
 *     int - 0 on success, -1 on failure.
 */
int queue_push(queue_t *queue, task_t *task);

/*
 * Pop a task from the queue.
 * Arguments:
 *     queue_t *queue - Self reference.
 * Returns:
 *     task_t * - The task.
 */
task_t *queue_pop(queue_t *queue);

#endif