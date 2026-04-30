#ifndef TASK_H
#define TASK_H

#include <stdint.h>

/*
 * TaskState determines the currnet state of a task.
 */
enum TaskState {
    Ready,      // Ready to run
    Running,    // Currently running
    Waiting,    // Yielded
    Done,       // Done
};

/*
 * A task_t acts as a state machine for coroutines/fibers.
 */
typedef struct {
    char *stack;            // Each task has a private stack frame
    uintptr_t sp;           // Pointer to the private stack
    enum TaskState state;   // Current task state
    void (*entry)();        // This is the task's work to complete
} task_t;

#endif