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

    // Otwieranie semaforów
    sem_t *semProd = openSemaphore("/sem_prod");
    sem_t *semCons = openSemaphore("/sem_cons");

    // Otwieranie pamięci dzielonej
    int shmFd = openSharedMemory("/shm_buffer");
    SegmentPD *sharedBuffer = (SegmentPD *)mapSharedMemory(shmFd, sizeof(SegmentPD));

    // Otwarcie pliku wejściowego
    int inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1) {
        perror("Błąd przy otwieraniu pliku wejściowego!");
        exit(EXIT_FAILURE);
    }

    char buffer[NELE];
    ssize_t bytesRead;

    while ((bytesRead = read(inputFd, buffer, NELE)) > 0)
    {
        // Czekanie na dostęp do bufora
        waitSemaphore(semProd);

        // Umieszczenie danych w buforze
        memcpy(sharedBuffer->bufor[sharedBuffer->wstaw], buffer, NELE);
        printf("Producent umieścił w buforze na pozycji: %d --> %s, wartość semafora producenta: %d, wartość semafora kosumaenta: %d\n", sharedBuffer->wstaw, buffer, getSemaphoreValue(semProd),  getSemaphoreValue(semCons));

        // Aktualizacja pozycji wstawiania
        sharedBuffer->wstaw = (sharedBuffer->wstaw + 1) % NBUF;

        // Zwolnienie dostępu do bufora
        postSemaphore(semCons);

        sleep(rand() % (3 - 0 + 1) + 0); // losowo od 0 do 3 sec
    }

    close(inputFd);

    // Sygnał zakończenia przesyłania danych
    memset(buffer, '\0', NELE);
    waitSemaphore(semProd);
    memcpy(sharedBuffer->bufor[sharedBuffer->wstaw], buffer, NELE);
    sharedBuffer->wstaw = (sharedBuffer->wstaw + 1) % NBUF;
    postSemaphore(semCons);

    exit(EXIT_SUCCESS);
}