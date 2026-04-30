#include <stdlib.h>
#include <string.h>

#include "stack.h"

// This function will be the entry point for a task.
extern void trampoline();

/*
 * Allocate a stack.
 * Returns:
 *     char * - Stack data.
 */
char *alloc_stack() {
    return (char *)malloc(STACK_SIZE);
}

/*
 * Initialize a task's stack for the first call.
 * Arguments:
 *     task_t *task - Task to initialize.
 */
void init_stack(task_t *task) {
    char *stack_top = task->stack + STACK_SIZE;
    uintptr_t sp = (uintptr_t)stack_top;
    uintptr_t trampoline_ptr = (uintptr_t)trampoline;

    // Align to 16 bytes
    sp &= ~((uintptr_t)0xF);

    // Push return address (trampoline)
    sp -= sizeof(uintptr_t);
    memcpy(&task->stack[sp], &trampoline_ptr, sizeof(uintptr_t));

    // Push callee-saved registers (rbx, rbp, r12-r15)
    for(int i = 0; i < 6; i++) {
        sp -= sizeof(uintptr_t);
        memset(&task->stack[sp], 0, sizeof(uint64_t));
    }

    task->sp = sp;
}