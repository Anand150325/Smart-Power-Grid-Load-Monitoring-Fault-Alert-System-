#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "signal.h"

// Ctrl+C handler
void handle_sigint(int sig) {
    printf("\nSystem shutting down...\n");
    exit(0);
}

// Initialize signals
int signal_init() {

    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        perror("signal error");
        return -1;
    }

    return 0;
}
