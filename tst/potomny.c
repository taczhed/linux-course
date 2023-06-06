#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include "library.h"
#include <unistd.h>

void criticalSection(int section, sem_t *semaphore) {
    printf("        Sekcja %d procesu %d: Przed sekcją krytyczną\n", section, getpid());
    printf("        Wartość semafora przed sekcją krytyczną: %d, PID: %d\n", getSemaphoreValue(semaphore), getpid());
    printf("        Wartośc w pliku przed sekcją krytyczną: %d\n", readFileData(openFile(FILE_NAME)));

    sem_wait(semaphore);
    int file = openFile(FILE_NAME);

    int value = readFileData(file);
    int newValue = value + 1;

    modifyFileData(file, newValue);

    sleep(rand() % 3 + 1);
    printf("        Wartość semafora wewnątrz sekcji krytycznej: %d\n", getSemaphoreValue(semaphore));
    printf("        Wartośc w pliku przed zapisaniem w sekcji krytycznej: %d\n", readFileData(openFile(FILE_NAME)));
    closeFile(file);

    int modifiedValue = readFileData(openFile(FILE_NAME));
    sem_post(semaphore);

    printf("        Wartość semafora po sekcji krytycznej: %d, PID: %d\n", getSemaphoreValue(semaphore), getpid());
    printf("        Sekcja %d procesu %d: Po sekcji krytycznej, nowa wartość: %d \n", section, getpid(), modifiedValue);
}


int main(int argc, char* argv[]) {
    printf("Proces potomny, pid: %d\n", getpid());
    if (argc < 2) {
        printf("Nieprawidłowe argumenty. Użyj: %s <liczba_sekcji_krytycznych>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int numSections = atoi(argv[1]);

    sem_t *semaphore = openSemaphore(SEMAPHORE_NAME);
    for (int section = 1; section <= numSections; ++section) {
        criticalSection(section, semaphore);
    }
    exit(EXIT_SUCCESS);
}
