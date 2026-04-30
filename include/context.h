#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdint.h>

extern void context_switch(uintptr_t *oldsp, uintptr_t new_sp);

#endif