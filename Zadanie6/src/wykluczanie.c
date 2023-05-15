#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <semaphore.h>
#include <time.h>
#include "sem_lib.h"

sem_t *sem;

void criticalSection(int processId, int sectionId)
{
    int fd = open("./src/number.txt", O_RDWR);
    if (fd == -1)
    {
        perror("open");
        exit(1);
    }
    char readBuf[10];
    read(fd, readBuf, sizeof(readBuf));
    int currentNumber = atoi(readBuf);

    lseek(fd, 0, SEEK_SET);
    char numStr[10];
    sprintf(numStr, "%d", currentNumber + 1);
    write(fd, numStr, strlen(numStr));

    close(fd);

    printf("Proces %d - Sekcja krytyczna %d: Obecna liczba = %d, Wartość semafora: %d\n", processId, sectionId, currentNumber, getSemaphoreValue(sem));

    srand(time(NULL));
    sleep(rand() % 5 + 1);
}

int main(int argc, char *argv[])
{
    sem = openSemaphore("sem");
    int processId = getpid();
    srand(processId);

    int numSections = atoi(argv[1]);
    int sectionId;

    for (sectionId = 0; sectionId < numSections; sectionId++)
    {
        printf("Proces %d - Sekcja krytyczna %d: Wchodzenie do sekcji krytycznej, wartość semafora: %d\n", processId, sectionId, getSemaphoreValue(sem));
        
        sleep(rand() % 5 + 1);
        
        waitSemaphore(sem);
        criticalSection(processId, sectionId);
        postSemaphore(sem);
        printf("Proces %d - Sekcja krytyczna %d: Wychodzenie z sekcji krytycznej, wartość semafora: %d\n", processId, sectionId, getSemaphoreValue(sem));
    }

    closeSemaphore(sem);

    return 0;
}