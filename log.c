#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "log.h"
#include <pthread.h>


int fd;
pthread_mutex_t log_mutex;

// Initialize log file
int log_init() {

    fd = open("grid_log.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);  //TRUNC removes earlier values
    pthread_mutex_init(&log_mutex, NULL);
  
    if (fd == -1) {
        perror("log open error");
        return -1;
    }

    return 0;
}

// Info log
int log_info(const char *msg) {
	
	pthread_mutex_lock(&log_mutex);  //LOCK Mutex
    
    	dprintf(fd, "[INFO] %s\n", msg);
    	
    	pthread_mutex_unlock(&log_mutex);  //Unlock Mutex
    	
    
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
    pthread_mutex_destroy(&log_mutex);
    
    return 0;
}
