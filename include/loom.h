#ifndef LOOM_H
#define LOOM_H

/*
 * Initialize the loom environment.
 */
void loom_init();

/* 
 * Cleanup the loom environment.
 */
void loom_deinit();

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

/*
 * Exit from a task.
 */
void loom_exit();

#endif