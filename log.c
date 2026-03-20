#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "log.h"

int fd;

// Initialize log file
int log_init() {

    fd = open("grid_log.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);  //TRUNC removes earlier values

    if (fd == -1) {
        perror("log open error");
        return -1;
    }

    return 0;
}

// Info log
int log_info(const char *msg) {
    dprintf(fd, "[INFO] %s\n", msg);
    return 0;
}

// Warning log
int log_warn(const char *msg) {
    dprintf(fd, "[WARN] %s\n", msg);
    return 0;
}

// Error log
int log_error(const char *msg) {
    dprintf(fd, "[ERROR] %s\n", msg);
    return 0;
}

// Close log file
int log_close() {
    close(fd);
    return 0;
}
