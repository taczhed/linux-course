#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <errno.h>

sem_t *createSemaphore(const char *name, unsigned int value) {
    sem_t *sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
    if (sem == SEM_FAILED) {
        perror("Nie można utworzyć semafora");
        exit(EXIT_FAILURE);
    }
    return sem;
}

sem_t *openSemaphore(const char *name) {
    sem_t *sem = sem_open(name, 0);
    if (sem == SEM_FAILED) {
        perror("Nie można otworzyć semafora");
        exit(EXIT_FAILURE);
    }
    return sem;
}

void closeSemaphore(sem_t *sem) {
    if (sem_close(sem) == -1) {
        perror("Nie można zamknąć semafora");
        exit(EXIT_FAILURE);
    }
}

void removeSemaphore(const char *name) {
    if (sem_unlink(name) == -1) {
        if (errno != ENOENT) {
            perror("Błąd podczas usuwania semafora");
            exit(EXIT_FAILURE);
        }
    }
}

void waitSemaphore(sem_t *sem) {
    if (sem_wait(sem) == -1) {
        perror("Nie można oczekiwać na semaforze");
        exit(EXIT_FAILURE);
    }
}

void postSemaphore(sem_t *sem) {
    if (sem_post(sem) == -1) {
        perror("Nie można podnieść semafora");
        exit(EXIT_FAILURE);
    }
}

int getSemaphoreValue(sem_t *sem) {
    int value;
    if (sem_getvalue(sem, &value) == -1) {
        perror("Nie można pobrać wartości semafora");
        exit(EXIT_FAILURE);
    }
    return value;
}