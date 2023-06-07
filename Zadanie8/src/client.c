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

char queue_name[MAX_QUEUE_NAME_SIZE];

void cleanup() {
    // Zamknij i usuń kolejkę klienta
    mq_close(queue_name);
    mq_unlink(queue_name);
}

void sigint_handler(int signum) {
    exit(0);
}

int main() {
    // Utwórz nazwę kolejki klienta na podstawie PID
    pid_t pid = getpid();
    snprintf(queue_name, MAX_QUEUE_NAME_SIZE, "/%d", pid);

    // Utwórz kolejkę klienta
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_BUFFER_SIZE;
    attr.mq_curmsgs = 0;

    mqd_t client_queue = mq_open(queue_name, O_CREAT | O_RDONLY | O_EXCL, 0666, &attr);
    if (client_queue == (mqd_t)-1) {
        perror("Nie można otworzyć kolejki klienta");
        exit(1);
    }

    // Zarejestruj funkcje do czyszczenia i obsługi sygnału SIGINT
    atexit(cleanup);
    signal(SIGINT, sigint_handler);

    // Otwórz kolejkę serwera
    mqd_t server_queue = mq_open(SERVER_QUEUE_NAME, O_WRONLY);
    if (server_queue == (mqd_t)-1) {
        perror("Nie można otworzyć kolejki serwera");
        exit(1);
    }

    // Wypisz informację o kolejce klienta
    printf("Kolejka klienta: %s\n", queue_name);

    while (1) {
        // Wczytaj żądane działanie od użytkownika
        char buffer[MAX_BUFFER_SIZE];
        printf("Podaj działanie arytmetyczne (np. 2+3): ");
        if (fgets(buffer, MAX_BUFFER_SIZE, stdin) == NULL)
            break;

        // Wyślij komunikat do serwera
        char message[MAX_BUFFER_SIZE + MAX_QUEUE_NAME_SIZE];
        snprintf(message, MAX_BUFFER_SIZE + MAX_QUEUE_NAME_SIZE, "%s %s", queue_name, buffer);

        if (mq_send(server_queue, message, strlen(message), 0) == -1) {
            perror("Błąd podczas wysyłania komunikatu do serwera");
            exit(1);
        }

        // Odbierz wynik z kolejki klienta
        char response[MAX_BUFFER_SIZE];
        unsigned int prio;
        ssize_t response_length = mq_receive(client_queue, response, MAX_BUFFER_SIZE, &prio);
        if (response_length == -1) {
            perror("Błąd podczas odbierania odpowiedzi od serwera");
            exit(1);
        }

        // Wypisz otrzymany wynik
        response[response_length] = '\0';
        printf("Wynik: %s\n", response);
    }

    return 0;
}
