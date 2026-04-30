#include <stdio.h>

#include "loom.h"

void taskA() {
    while(1) {
        printf("A\n");
        loom_yield();
    }
}

void taskB() {
    while(1) {
        printf("B\n");
        loom_yield();
    }
}

int main(int argc, char **argv) {
    loom_init();

    loom_spawn(taskA);
    loom_spawn(taskB);

    loom_run();
    return 0;
}