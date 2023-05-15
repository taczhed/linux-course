#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <signal.h>
#include "sem_lib.h"

// ./powielacz ./wykluczanie 2 2

// dla 2 2 z sekcja krytyczna -> 4
// dla 2 2 z bez sekcji krytycznej -> 0

sem_t *sem; // deklaracja wskaźnika na semafor

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Użycie: %s <program> <liczba procesów> <liczba sekcji>\n", argv[0]);
        return 1;
    }

    char *programName = argv[1];
    int numProcesses = atoi(argv[2]), semValue;

    sem = createSemaphore("sem", 1); // inicjalizacja semafora

    printf("Adres semafora: %p\n", (void *)sem);
    semValue = getSemaphoreValue(sem);
    printf("Wartość początkowa semafora: %d\n", semValue);

    atexit(exitHandler);
    signal(SIGINT, sigintHandler);

    int fd = open("./src/number.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char numStr[10];
    sprintf(numStr, "%d", 0);
    write(fd, numStr, strlen(numStr));
    close(fd);

    int i;
    for (i = 0; i < numProcesses; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            execlp(programName, programName, argv[3], NULL); // wykluczanie
            perror("execlp");
            return 1;
        } else if (pid < 0) {
            perror("fork");
            return 1;
        }
    }

    for (i = 0; i < numProcesses; i++) {
        wait(NULL);
    }

    fd = open("./src/number.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char readBuf[10];
    read(fd, readBuf, sizeof(readBuf));
    int finalNumber = atoi(readBuf);

    printf("Końcowy numer: %d\n", finalNumber);
    printf("Sprawdzenie : %d\n", atoi(argv[2]) * atoi(argv[2]));

    close(fd);
    closeSemaphore(sem);
    removeSemaphore("sem");

    return 0;
}