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

char queueName[MAX_QUEUE_NAME_SIZE];

void cleanup() {
    mq_close(queueName);
    mq_unlink(queueName);
}

void sigint_handler(int signum) {
    exit(0);
}

int main() {
    // nazwa kolejki klienta na podstawie PID
    pid_t pid = getpid();
    snprintf(queueName, MAX_QUEUE_NAME_SIZE, "/%d", pid);

    // kolejka klienta
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_BUFFER_SIZE;
    attr.mq_curmsgs = 0;

    mqd_t clientQueue = mq_open(queueName, O_CREAT | O_RDONLY | O_EXCL, 0666, &attr);
    if (clientQueue == (mqd_t)-1) {
        perror("Nie można otworzyć kolejki klienta");
        exit(1);
    }

    atexit(cleanup);
    signal(SIGINT, sigint_handler);

    // kolejka serwera
    mqd_t serverQueue = mq_open(SERVER_QUEUE_NAME, O_WRONLY);
    if (serverQueue == (mqd_t)-1) {
        perror("Nie można otworzyć kolejki serwera");
        exit(1);
    }

    printf("Kolejka klienta: %s\n", queueName);

    while (1) {
        // input
        char buffer[MAX_BUFFER_SIZE];
        printf("Podaj działanie arytmetyczne (np. 2+2): ");
        if (fgets(buffer, MAX_BUFFER_SIZE, stdin) == NULL)
            break;

        // post
        char message[MAX_BUFFER_SIZE + MAX_QUEUE_NAME_SIZE];
        snprintf(message, MAX_BUFFER_SIZE + MAX_QUEUE_NAME_SIZE, "%s %s", queueName, buffer);

        if (mq_send(serverQueue, message, strlen(message), 0) == -1) {
            perror("Błąd podczas wysyłania komunikatu do serwera");
            exit(1);
        }

        // await res
        char response[MAX_BUFFER_SIZE];
        unsigned int prio;
        ssize_t responseLength = mq_receive(clientQueue, response, MAX_BUFFER_SIZE, &prio);
        if (responseLength == -1) {
            perror("Błąd podczas odbierania odpowiedzi od serwera");
            exit(1);
        }

        // wynik
        response[responseLength] = '\0';
        printf("Wynik: %s\n", response);
    }

    return 0;
}
