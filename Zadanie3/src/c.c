#define _POSIX_C_SOURCE 200112L
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Błąd wejścia\n");
        return 1;
    }

    pid_t pid;
    int mode, signalNumber, status;

    sscanf(argv[1], "%d", &mode);
    sscanf(argv[2], "%d", &signalNumber);

    printf("Uruchomiono c, PID: %d, tryb: %d, sygnał: %d\n", getpid(), mode, signalNumber);

    pid = fork();
    if (pid == 0) {
        execl("./execdir/c1.x", "./execdir/c1.x", argv[1], argv[2], NULL);
        printf("Błąd podczas uruchamiania c1.\n");
        exit(1);
    }
    else if (pid > 0) {

        sleep(1);

        // Wysłanie sygnału do grupy procesów
        printf("Wysyłam do grupy %d sygnał  %d...\n", pid, signalNumber);
        killpg(pid, signalNumber);

        wait(&status);
        printf("Proces macierzysty c zakończył działanie ze statusem: %d\n", status);
    }
    else {
        printf("Błąd podczas tworzenia procesu potomnego.\n");
        exit(1);
    }

    return 0;
}