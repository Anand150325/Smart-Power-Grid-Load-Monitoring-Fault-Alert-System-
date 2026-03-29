#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "ipc.h"
#include "log.h"
#include "config.h"

// Initialize system
int controller_init() {

    if (comm_init() == Failure) {
        printf("Communication init failed\n");
        return Failure;
    }

    if (log_init() != 0) {
        printf("Log init failed\n");
        return Failure;
    }

    return Success;
}

// Start system
void controller_start() {

    pid_t pid;
    int pipefd[2];

    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe error");
        exit(1);
    }

    // ALERT PROCESS
    pid_t alert_pid = fork();

    if (alert_pid == 0) {

        close(pipefd[1]);  // close write end

        char alert_msg[150];

        while (1) {
            int n = read(pipefd[0], alert_msg, sizeof(alert_msg));

            if (n > 0) {
                printf("🚨 ALERT Generated: %s\n", alert_msg);
            }
        }
    }

    // Controller closes read end
    close(pipefd[0]);

    // CREATE SUBSTATIONS
    for (int i = 1; i <= 3; i++) {

        pid = fork();

        if (pid == -1) {
            perror("fork error");
        }

        else if (pid == 0) {

            struct msg m;

            while (1) {

                m.id = i;
                m.voltage = rand()%40 + 200;
                m.current = rand()%20 + 5;
                m.load = m.voltage * m.current;

                if (comm_send(&m) == -1) {
                    perror("Send failed");
                }

                sleep(2);
            }
        }
    }

    // CONTROLLER LOOP
    struct msg data;

    while (1) {

        if (comm_receive(&data) == -1) {
            log_error("Receive failed");
            continue;
        }

        char buffer[150];
        char *status;

        // STATUS CHECK
        if (data.load > MAX_LOAD) {
            status = "OVERLOAD";
        }
        else if (data.voltage < MIN_VOLTAGE) {
            status = "LOW VOLTAGE";
        }
        else {
            status = "NORMAL";
        }

        // PRINT
        printf("STATUS=%s | ID=%d V=%d I=%d Load=%d\n",
               status, data.id, data.voltage, data.current, data.load);

        // LOG
        sprintf(buffer, "STATUS=%s | ID=%d V=%d I=%d Load=%d",
                status, data.id, data.voltage, data.current, data.load);

        log_info(buffer);

        // ALERT ONLY (NO STOP)
        if (data.load > MAX_LOAD || data.voltage < MIN_VOLTAGE) {

            log_warn("FAULT DETECTED");

            char alert_msg[150];

            sprintf(alert_msg,
                    "ID=%d | V=%d | I=%d | Load=%d | STATUS=%s",
                    data.id, data.voltage, data.current, data.load, status);

            write(pipefd[1], alert_msg, strlen(alert_msg) + 1);
        }
    }
}
