#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "semafor.h"
#include "pamiec_dzielona.h"

#define NELE 2 // Rozmiar elementu bufora (jednostki towaru) w bajtach
#define NBUF 3 // Liczba elementów bufora

int main(int argc, char **argv)
{

    srand(time(NULL));

    // removeSemaphore("/sem_prod"); 
    // removeSemaphore("/sem_cons");
    // removeSharedMemory("/shm_buffer");

    // Tworzenie semaforów
    sem_t *semProd = createSemaphore("/sem_prod", 1);
    sem_t *semCons = createSemaphore("/sem_cons", 0);

    printf("Adres sem_prod: %p\n", &semProd);
    printf("Wartość początkowa sem_prod: %d\n", getSemaphoreValue(semProd));

    printf("Adres sem_cons: %p\n", &semCons);
    printf("Wartość początkowa sema_cons: %d\n", getSemaphoreValue(semCons));

    // Tworzenie pamięci dzielonej
    int shmFd = createSharedMemory("/shm_buffer", sizeof(SegmentPD));
    SegmentPD *sharedBuffer = (SegmentPD *)mapSharedMemory(shmFd, sizeof(SegmentPD));

    // Inicjalizacja pamięci dzielonej
    sharedBuffer->wstaw = 0;
    sharedBuffer->wyjmij = 0;

    pid_t pidProducer, pidConsumer;

    pidProducer = fork();
    if (pidProducer == -1) {
        perror("Błąd w fork() dla producenta!");
        exit(EXIT_FAILURE);
    }

    if (pidProducer == 0) {
        // Uruchamiamy producenta...
        execlp("./execdir/producent.x", "./execdir/producent.x", argv[1], argv[2], NULL);
        perror("Błąd execlp producent");
        exit(1);
    }

    pidConsumer = fork();
    if (pidConsumer == -1) {
        perror("Błąd w fork() dla konsumenta!");
        exit(EXIT_FAILURE);
    }

    if (pidConsumer == 0) {
        // Uruchamiamy kosumaneta...
        execlp("./execdir/konsument.x", "./execdir/konsument.x", argv[1], argv[2], NULL);
        perror("Błąd execlp konsument");
        exit(1);
    }

    // Proces macierzysty
    waitpid(pidProducer, NULL, 0);
    waitpid(pidConsumer, NULL, 0);

    // Porządki przed zakończeniem programu
    closeSharedMemory(sharedBuffer, sizeof(SegmentPD));
    removeSharedMemory("/shm_buffer");

    closeSemaphore(semProd);
    closeSemaphore(semCons);
    removeSemaphore("/sem_prod");
    removeSemaphore("/sem_cons");

    return 0;
}