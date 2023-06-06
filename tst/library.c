#include "library.h"
#include "stdio.h"
#include "signal.h"
#include "stdlib.h"
#include <semaphore.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

void createOrUseExistingFile(char *fileName, int initialValue) {
    int fileDescriptor = open(fileName, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fileDescriptor == -1) {
        perror("Błąd tworzenia pliku");
        exit(EXIT_FAILURE);
    }
    modifyFileData(fileDescriptor, initialValue);
    closeFile(fileDescriptor);
}

int openFile(char *fileName) {
    int fileDescriptor = open(fileName, O_RDWR);
    if (fileDescriptor == -1) {
        perror("Błąd otwierania pliku");
        exit(EXIT_FAILURE);
    }
    return fileDescriptor;
}

void closeFile(int fileDescriptor) {
    close(fileDescriptor);
}

int readFileData(int fileDescriptor) {
    int value;
    if (read(fileDescriptor, &value, sizeof(value)) == -1) {
        perror("Błąd odczytu pliku");
        exit(EXIT_FAILURE);
    }
    return value;
}

void modifyFileData(int fileDescriptor, int newValue) {
    if (lseek(fileDescriptor, 0, SEEK_SET) == -1) {
        perror("Błąd ustawiania wskaźnika pliku");
        exit(EXIT_FAILURE);
    }
    if (write(fileDescriptor, &newValue, sizeof(newValue)) == -1) {
        perror("Błąd zapisu do pliku");
        exit(EXIT_FAILURE);
    }
}

sem_t *createSemaphore(char *semaphoreName, int value) {
    printf("Tworzenie semafora %s\n", semaphoreName);
    sem_t *semaphore = sem_open(semaphoreName, O_CREAT | O_EXCL, 0666, value);
    if (semaphore == SEM_FAILED) {
        perror("Błąd tworzenia semafora");
        exit(EXIT_FAILURE);
    }
    return semaphore;
}

sem_t *openSemaphore(char *semaphoreName) {
    printf("Otwieranie semafora %s\n", semaphoreName);
    sem_t *semaphore = sem_open(semaphoreName, 0);
    if (semaphore == SEM_FAILED) {
        perror("Błąd otwierania semafora");
        exit(EXIT_FAILURE);
    }
    return semaphore;
}

int getSemaphoreValue(sem_t *semaphore) {
    int semaphoreValue;
    sem_getvalue(semaphore, &semaphoreValue);
    if (semaphoreValue < 0) {
        perror("Błąd pobierania wartości semafora");
        exit(EXIT_FAILURE);
    }

    return semaphoreValue;
}

void closeSemaphore(char *semaphoreName) {
    printf("Zamykanie semafora %s\n", semaphoreName);
    sem_t *semaphore = sem_open(semaphoreName, 0);
    if (semaphore == SEM_FAILED) {
        perror("Błąd otwierania semafora");
        exit(EXIT_FAILURE);
    }
    sem_close(semaphore);
}

void deleteSemaphore(char *semaphoreName) {
    printf("Usuwanie semafora %s\n", semaphoreName);
    if (sem_unlink(semaphoreName) < 0) {
        if (errno != ENOENT) {
            perror("Błąd podczas usuwania semafora");
            exit(EXIT_FAILURE);
        }
    }
}

void handleSignal(int signal) {
    if (signal == SIGINT) {
        printf("Otrzymano sygnał SIGINT\n");
        exit(0);
    }
}