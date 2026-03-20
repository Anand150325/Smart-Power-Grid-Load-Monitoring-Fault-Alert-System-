#ifndef IPC_H
#define IPC_H

#include <mqueue.h>
#include "config.h"

//Optimized message structure
struct msg {
    short id;        // Substation ID
    short voltage;   // Voltage
    short current;   // Current
    int load;        // Load
};

// APIs
int comm_init();
int comm_send(struct msg *m);
int comm_receive(struct msg *m);
int comm_cleanup();

#endif
