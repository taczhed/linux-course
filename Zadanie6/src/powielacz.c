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

sem_t *sem; // deklaracja wskaźnika na semafor

// wyjście z programu
void exit_handler() {
    sem_unlink("/semaphore");
}

// obsługa sygnału Ctrl+C
void sigint_handler(int signum) {
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Użycie: %s <program> <liczba procesow> <liczba sekcji>\n", argv[0]);
        return 1;
    }

    char *programName = argv[1];
    int numProcesses = atoi(argv[2]), semValue;

    sem = sem_open("/semaphore", O_CREAT | O_EXCL, 0666, 1); // inicjalizacja semafora
    if (sem == SEM_FAILED) {
        perror("sem_open");
        return 1;
    }

    printf("Adres semafora: %p\n", (void *)sem);
    sem_getvalue(sem, &semValue);
    printf("Wartość początkowa semafora: %d\n", semValue);

    atexit(exit_handler);
    signal(SIGINT, sigint_handler);

    int fd = open("numer.txt", O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0666);
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

    fd = open("numer.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char readBuf[10];
    read(fd, readBuf, sizeof(readBuf));
    int finalNumber = atoi(readBuf);

    printf("Końcowy numer: %d\n", finalNumber);

    close(fd);
    sem_close(sem);
    sem_unlink("/semaphore");

    return 0;
}