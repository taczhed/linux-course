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

void handle_sigint(int sig) {
    cleanup();
    exit(EXIT_SUCCESS);
}

void calculate_expression(const char* expression, char* result) {
    int num1, num2;
    char op;

    sscanf(expression, "%d %c %d", &num1, &op, &num2);

    switch (op) {
        case '+':
            snprintf(result, MESSAGE_SIZE, "%d", num1 + num2);
            break;
        case '-':
            snprintf(result, MESSAGE_SIZE, "%d", num1 - num2);
            break;
        case '*':
            snprintf(result, MESSAGE_SIZE, "%d", num1 * num2);
            break;
        case '/':
            if (num2 != 0) {
                snprintf(result, MESSAGE_SIZE, "%d", num1 / num2);
            } else {
                snprintf(result, MESSAGE_SIZE, "Error: Division by zero");
            }
            break;
        default:
            snprintf(result, MESSAGE_SIZE, "Error: Invalid operator");
            break;
    }
}

void cleanup() {
    mq_close(server_queue);
    mq_unlink(SERVER_QUEUE_NAME);
}

int main() {
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(struct message);
    attr.mq_curmsgs = 0;

    server_queue = mq_open(SERVER_QUEUE_NAME, O_RDONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, &attr);
    if (server_queue == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, handle_sigint);

    atexit(cleanup);

    struct message msg;
    char result[MESSAGE_SIZE];
    mqd_t client_queue;

    while (1) {
        if (mq_receive(server_queue, (char *)&msg, sizeof(struct message), NULL) == -1) {
            perror("mq_receive");
            exit(EXIT_FAILURE);
        }

        client_queue = mq_open(msg.expression, O_WRONLY);
        if (client_queue == (mqd_t)-1) {
            perror("mq_open");
            exit(EXIT_FAILURE);
        }

        calculate_expression(msg.expression + sizeof(pid_t), result);

        if (mq_send(client_queue, result, strlen(result) + 1, 0) == -1) {
            perror("mq_send");
            exit(EXIT_FAILURE);
        }

        mq_close(client_queue);
    }

    return 0;
}