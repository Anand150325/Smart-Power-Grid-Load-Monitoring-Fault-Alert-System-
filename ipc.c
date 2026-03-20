 #include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include "ipc.h"

static mqd_t mq;   // Message queue descriptor

// Initialize message queue
int comm_init() {

    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(struct msg);
    attr.mq_curmsgs = 0;

    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0644, &attr);

    if (mq == (mqd_t)-1) {
        perror("mq_open error");
        return Failure;
    }

    return Success;
}

// Send message
int comm_send(struct msg *m) {

    if (mq_send(mq, (char*)m, sizeof(struct msg), 0) == -1) {
        perror("mq_send error");
        return Failure;
    }

    return Success;
}

// Receive message
int comm_receive(struct msg *m) {

    if (mq_receive(mq, (char*)m, sizeof(struct msg), NULL) == -1) {
        perror("mq_receive error");
        return Failure;
    }

    return Success;
}

// Cleanup queue
int comm_cleanup() {
    mq_close(mq);
    mq_unlink(QUEUE_NAME);
    return Success;
}
