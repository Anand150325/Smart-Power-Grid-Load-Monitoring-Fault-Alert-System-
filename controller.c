#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ipc.h"     // communication API
#include "log.h"      // logging API
#include "config.h"

// Initialize system (IPC + Logging)
int controller_init() {

    if (comm_init() == Failure) {   // initialize message queue
        printf("Communication init failed\n");
        return Failure;
    }

    if (log_init() != 0) {          // initialize log file
        printf("Log init failed\n");
        return Failure;
    }

    return Success;
}

// Start system
void controller_start() {

    pid_t pid;

    // Create 3 substations (child processes)
    for (int i = 1; i <= 3; i++) {

        pid = fork();   // create new process

        if (pid == -1) {
            perror("fork error");
        }

        else if (pid == 0) {
            // Child process to Substation

            struct msg m;

            while (1) {
                m.id = i;

                // Generate random values
                m.voltage = rand()%40 + 200;
                m.current = rand()%20 + 5;
                m.load = m.voltage * m.current;

                // Send data to controller
                if (comm_send(&m) == -1) {
                    perror("Send failed");
                }

                sleep(2);  // wait 2 seconds
            }
        }
    }

    // Parent process to Controller
    struct msg data;

  while (1) {

    if (comm_receive(&data) == -1) {
        log_error("Receive failed");
        continue;
    }

    char buffer[150];
    char *status;

    // Determine status
    if (data.load > MAX_LOAD) {
        status = "OVERLOAD";
    }
    else if (data.voltage < MIN_VOLTAGE) {
        status = "LOW VOLTAGE";
    }
    else {
        status = "NORMAL";
    }

    // Display
    printf("STATUS=%s  ID=%d V=%d I=%d Load=%d\n",status, data.id, data.voltage, data.current, data.load);
    // Log to file
    sprintf(buffer, "STATUS=%s  ID=%d V=%d I=%d Load=%d", status, data.id, data.voltage, data.current, data.load);
    log_info(buffer);
}
}
