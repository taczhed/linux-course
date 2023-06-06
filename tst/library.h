#ifndef INC_6_LIBRARY_H
#define INC_6_LIBRARY_H
#include "stdio.h"
#include <semaphore.h>

#define SEMAPHORE_NAME "/semafor_zadania_6a"
#define FILE_NAME "numer.txt"

void createOrUseExistingFile(char *fileName, int initialValue);

int openFile(char *fileName);

void closeFile(int fileDescriptor);

int readFileData(int fileDescriptor);

void modifyFileData(int fileDescriptor, int newValue);

sem_t *createSemaphore(char *semaphoreName, int value);

sem_t *openSemaphore(char *semaphoreName);

int getSemaphoreValue(sem_t *sem_t);

void closeSemaphore(char *semaphoreName);

void deleteSemaphore(char *semaphoreName);

void handleSignal(int signal);

#endif //INC_6_LIBRARY_H
