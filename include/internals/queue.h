#ifndef QUEUE_H
#define QUEUE_H

#include "task.h"

/*
 * Queue is implemented as a linked list.
 */
struct node {
    task_t *value;
    struct node *next;
};

/*
 * A queue is just a FIFO of tasks.
 */
typedef struct {
    struct node *head;
    struct node *tail;
    size_t size;
} queue_t;

/*
 * Initialize a queue.
 * Returns:
 *     queue_t * - New queue.
 */
queue_t *init_queue();

/*
 * Delete a queue.
 * Arguments:
 *     queue_t *q - Self reference.
 */
void free_queue(queue_t *q);

/*
 * Push a task to the queue.
 * Arguments:
 *     queue_t *q - Self reference.
 *     task_t *task - Push this task.
 * Returns:
 *     int - 0 on success, -1 on failure.
 */
int queue_push(queue_t *q, task_t *task);

/*
 * Pop a task from the queue.
 * Arguments:
 *     queue_t *q - Self reference.
 * Returns:
 *     task_t * - The task.
 */
task_t *queue_pop(queue_t *q);

#endif