#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <signal.h>
#include "common.h"

void cleanup();

mqd_t server_queue;
mqd_t client_queue;

void handle_sigint(int sig) {
    cleanup();
    exit(EXIT_SUCCESS);
}

void cleanup() {
    if (client_queue != (mqd_t)-1) {
        mq_close(client_queue);
        char client_queue_name[20];
        snprintf(client_queue_name, sizeof(client_queue_name), "/%d", getpid());
        mq_unlink(client_queue_name);
    }

    if (server_queue != (mqd_t)-1) {
        mq_close(server_queue);
    }
}

int main() {
    char server_queue_name[] = SERVER_QUEUE_NAME;
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(struct message);
    attr.mq_curmsgs = 0;

    server_queue = mq_open(server_queue_name, O_WRONLY);
    if (server_queue == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    char client_queue_name[20];
    snprintf(client_queue_name, sizeof(client_queue_name), "/%d", getpid());

    client_queue = mq_open(client_queue_name, O_RDONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, &attr);
    if (client_queue == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, handle_sigint);
    atexit(cleanup);

    printf("Client PID: %d\n", getpid());
    printf("Client queue name: %s\n", client_queue_name);

    struct message msg;
    char result[MESSAGE_SIZE];
    ssize_t bytes_read;

    while (1) {
        printf("Enter an expression (e.g., num1 op num2): ");
        fflush(stdout);

        if (fgets(msg.expression + sizeof(pid_t), MESSAGE_SIZE - sizeof(pid_t), stdin) == NULL) {
            break;
        }

        msg.client_pid = getpid();

        if (mq_send(server_queue, (const char *)&msg, sizeof(struct message), 0) == -1) {
            perror("mq_send");
            exit(EXIT_FAILURE);
        }

        bytes_read = mq_receive(client_queue, result, MESSAGE_SIZE, NULL);
        if (bytes_read == -1) {
            perror("mq_receive");
            exit(EXIT_FAILURE);
        }

        printf("Result: %s\n", result);
    }

    return 0;
}