#ifndef SEMAFOR_H
#define SEMAFOR_H

#include <semaphore.h>

sem_t *createSemaphore(const char *name, int value);
sem_t *openSemaphore(const char *name);
void closeSemaphore(sem_t *sem);
void removeSemaphore(const char *name);
void waitSemaphore(sem_t *sem);
void postSemaphore(sem_t *sem);
int getSemaphoreValue(sem_t *sem);

#endif  /* SEMAFOR_H */