#ifndef COMMON_H
#define COMMON_H

#define MESSAGE_SIZE 256
#define SERVER_QUEUE_NAME "/server_queue"

struct message {
    pid_t client_pid;
    char expression[MESSAGE_SIZE];
};

#endif