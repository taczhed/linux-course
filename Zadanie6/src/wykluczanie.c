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

void criticalSection(int processId, int sectionId) {
    int fd = open("numer.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    char readBuf[10];
    read(fd, readBuf, sizeof(readBuf));
    int currentNumber = atoi(readBuf);
    int newNumber = currentNumber + 1;

    lseek(fd, 0, SEEK_SET);
    char numStr[10];
    sprintf(numStr, "%d", newNumber);
    write(fd, numStr, strlen(numStr));

    close(fd);

    printf("Proces %d - Sekcja krytyczna %d: Obecna liczba = %d, Nowa liczba = %d\n", processId, sectionId, currentNumber, newNumber);

    srand(time(NULL));
    int sleepTime = rand() % 5 + 1;
    sleep(sleepTime);

    printf("Proces %d - Sekcja krytyczna %d: Wychodzenie z sekcji krytycznej\n", processId, sectionId);
}

int main(int argc, char *argv[]) {
    sem = openSemaphore("/semaphore");

    int processId = getpid();
    srand(processId);

    int numSections = atoi(argv[1]);
    int sectionId;

    for (sectionId = 0; sectionId < numSections; sectionId++) {
        waitSemaphore(sem);
        printf("Proces %d - Sekcja krytyczna %d: Wchodzenie do sekcji krytycznej\n", processId, sectionId);
        criticalSection(processId, sectionId);
        postSemaphore(sem);
    }

    closeSemaphore(sem);

    return 0;
}