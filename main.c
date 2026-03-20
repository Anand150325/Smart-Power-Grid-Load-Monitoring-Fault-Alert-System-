#include <stdio.h>
#include "config.h"
#include "controller.h"
#include "signal.h"


int main() {

    printf("Starting Smart Grid System...\n");

    // Initialize signal handling
    if (signal_init() == -1) {
        printf("Signal init failed\n");
        return -1;
    }

    // Initialize controller (IPC + logging)
    if (controller_init() == -1) {
        printf("System initialization failed\n");
        return -1;
    }

    // Start system
    controller_start();

    return 0;
}
