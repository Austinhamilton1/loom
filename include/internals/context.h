#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdint.h>

extern void context_switch(uintptr_t *old_sp, uintptr_t new_sp);

#endif