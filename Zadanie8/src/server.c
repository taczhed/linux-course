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
#define SERVER_QUEUE_NAME "/server_queue_2"

void cleanup() {
    // Zamknij i usuń kolejkę serwera
    mq_unlink(SERVER_QUEUE_NAME);
}

void sigint_handler(int signum) {
    exit(0);
}

int main() {
    // Utwórz kolejkę serwera
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_BUFFER_SIZE;
    attr.mq_curmsgs = 0;

    mqd_t server_queue = mq_open(SERVER_QUEUE_NAME, O_CREAT | O_RDONLY | O_EXCL, 0666, &attr);
    if (server_queue == (mqd_t)-1) {
        perror("Nie można utworzyć kolejki serwera");
        exit(1);
    }

    // Zarejestruj funkcję do czyszczenia i obsługi sygnału SIGINT
    atexit(cleanup);
    signal(SIGINT, sigint_handler);

    // Wypisz informację o kolejce serwera
    printf("Kolejka serwera: %s\n", SERVER_QUEUE_NAME);

    while (1) {
        // Odbierz komunikat z kolejki serwera
        char buffer[MAX_BUFFER_SIZE + MAX_QUEUE_NAME_SIZE];
        unsigned int prio;
        ssize_t message_length = mq_receive(server_queue, buffer, MAX_BUFFER_SIZE + MAX_QUEUE_NAME_SIZE, &prio);
        if (message_length == -1) {
            perror("Błąd podczas odbierania komunikatu od klienta");
            exit(1);
        }

        buffer[message_length] = '\0';

        // Odczytaj PID klienta i nazwę jego kolejki
        char client_pid_str[MAX_QUEUE_NAME_SIZE];
        sscanf(buffer, "/%[^ ]", client_pid_str);

        pid_t client_pid = atoi(client_pid_str);

        char client_queue_name[MAX_QUEUE_NAME_SIZE];
        snprintf(client_queue_name, MAX_QUEUE_NAME_SIZE, "/%d", client_pid);

        // Otwórz kolejkę klienta
        mqd_t client_queue = mq_open(client_queue_name, O_WRONLY);
        if (client_queue == (mqd_t)-1) {
            perror("Nie można otworzyć kolejki klienta");
            exit(1);
        }

        // Wykonaj działanie arytmetyczne
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

        // Przygotuj komunikat z wynikiem
        char response[MAX_BUFFER_SIZE];
        snprintf(response, MAX_BUFFER_SIZE, "%d", result);

        // Wyślij odpowiedź do klienta
        if (mq_send(client_queue, response, strlen(response), 0) == -1) {
            perror("Błąd podczas wysyłania odpowiedzi do klienta");
            exit(1);
        }

        // Zamknij kolejkę klienta
        mq_close(client_queue);
    }

    return 0;
}
