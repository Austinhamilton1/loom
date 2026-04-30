#ifndef LOOM_H
#define LOOM_H

#include "scheduler.h"

scheduler_t *global_scheduler = NULL;

/*
 * Initialize the loom environment.
 */
void loom_init();

/*
 * Spawn a new task in the loom environment.
 * Arguments:
 *     void (*entry)() - Pointer to a function to use as entry point for new task.
 */
void loom_spawn(void (*entry)());

/*
 * Start running the loom environment.
 */
void loom_run();

/*
 * Yield control to the loom environment.
 */
void loom_yield();

#endif