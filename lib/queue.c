#include <stdlib.h>

#include "queue.h"

/*
 * Initialize a queue.
 * Returns:
 *     queue_t * - New queue.
 */
queue_t *init_queue() {
    queue_t *q = (queue_t *)malloc(sizeof(queue_t));
    if(!q) return NULL;

    q->size = 0;
    q->head = NULL;
    q->tail = NULL;

    return q;
}

/*
 * Delete a queue.
 * Arguments:
 *     queue_t *q - Self reference.
 */
void free_queue(queue_t *q) {
    if(!q) return;

    struct node *ptr = q->head;
    while(ptr) {
        struct node *next = ptr->next;

        if(ptr->value) {
            free_task(ptr->value);
        }

        free(ptr);
        ptr = next;
    }

    free(q);
}

/*
 * Push a task to the queue.
 * Arguments:
 *     queue_t *q - Self reference.
 *     task_t *task - Push this task.
 * Returns:
 *     int - 0 on success, -1 on failure.
 */
int queue_push(queue_t *q, task_t *task) {
    if(!q || !task) return -1;

    // Initialize node
    struct node *n = (struct node *)malloc(sizeof(struct node));
    if(!n) return -1;

    n->value = task;
    n->next = NULL;

    if(q->tail) {
        q->tail->next = n;
    } else {
        q->head = n;
    }

    q->tail = n;
    q->size++;

    return 0;
}

/*
 * Pop a task from the queue.
 * Arguments:
 *     queue_t *q - Self reference.
 * Returns:
 *     task_t * - The task.
 */
task_t *queue_pop(queue_t *q) {
    if(!q || !q->head) return NULL;

    struct node *n = q->head;
    task_t *task = n->value;

    q->head = n->next;
    if(!q->head) {
        q->tail = NULL;
    }

    free(n);
    q->size--;

    return task;
}