#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#define MAX_BUFFER_SIZE 1024
#define MAX_QUEUE_NAME_SIZE 20
#define SERVER_QUEUE_NAME "/server_queue"

void cleanup() {
    mq_unlink(SERVER_QUEUE_NAME);
}

void sigint_handler(int signum) {
    exit(0);
}

int main() {
    // kolejka serwera
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_BUFFER_SIZE;
    attr.mq_curmsgs = 0;

    mqd_t serverQueue = mq_open(SERVER_QUEUE_NAME, O_CREAT | O_RDONLY | O_EXCL, 0666, &attr);
    if (serverQueue == (mqd_t)-1) {
        perror("Nie można utworzyć kolejki serwera");
        exit(1);
    }

    // clean i SIGINT
    atexit(cleanup);
    signal(SIGINT, sigint_handler);

    // start
    printf("Kolejka serwera: %s\n", SERVER_QUEUE_NAME);

    while (1) {
        // fetch handler?
        char buffer[MAX_BUFFER_SIZE + MAX_QUEUE_NAME_SIZE];
        unsigned int prio;
        ssize_t messageLength = mq_receive(serverQueue, buffer, MAX_BUFFER_SIZE + MAX_QUEUE_NAME_SIZE, &prio);
        if (messageLength == -1) {
            perror("Błąd podczas odbierania komunikatu od klienta");
            exit(1);
        }

        buffer[messageLength] = '\0';

        // req.params
        char clientPidStr[MAX_QUEUE_NAME_SIZE];
        sscanf(buffer, "/%[^ ]", clientPidStr);

        pid_t clientPid = atoi(clientPidStr);

        char clientQueueName[MAX_QUEUE_NAME_SIZE];
        snprintf(clientQueueName, MAX_QUEUE_NAME_SIZE, "/%d", clientPid);

        // kolejka klienta
        mqd_t clientQueue = mq_open(clientQueueName, O_WRONLY);
        if (clientQueue == (mqd_t)-1) {
            perror("Nie można otworzyć kolejki klienta");
            exit(1);
        }

        int num1, num2;
        char operator;
        sscanf(buffer, "/%*d %d %c %d", &num1, &operator, &num2);

        int result;
        switch (operator) {
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            case '/':
                result = num1 / num2;
                break;
            default:
                result = 0;
                break;
        }

        char response[MAX_BUFFER_SIZE];
        snprintf(response, MAX_BUFFER_SIZE, "%d", result);

        // req.json()
        if (mq_send(clientQueue, response, strlen(response), 0) == -1) {
            perror("Błąd podczas wysyłania odpowiedzi do klienta");
            exit(1);
        }

        mq_close(clientQueue);
    }

    return 0;
}
