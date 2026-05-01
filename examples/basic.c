#include <stdio.h>

#include "loom.h"

void taskA() {
    for(int i = 0; i < 10000; i += 2) {
        printf("%d ", i);
        loom_yield();
    }
}

void taskB() {
    for(int i = 1; i < 10000; i += 2) {
        printf("%d ", i);
        loom_yield();
    }
}

int main() {
    loom_init();

    loom_spawn(taskA);
    loom_spawn(taskB);

    loom_run();

    loom_deinit();
    return 0;
}