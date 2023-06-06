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

    // Otwarcie pliku wyjściowego
    int outputFd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (outputFd == -1)
    {
        perror("Błąd przy otwieraniu pliku wyjściowego!");
        exit(EXIT_FAILURE);
    }

    char buffer[NELE];
    ssize_t bytesWritten;

    while (1)
    {
        waitSemaphore(semCons); // Czekanie na dostęp do bufora

        // Pobranie danych z bufora
        memcpy(buffer, sharedBuffer->bufor[sharedBuffer->wyjmij], NELE);
        printf("Konsument pobrał wartość z pozycji: %d --> %s, , wartość semafora producenta: %d, wartość semafora kosumaenta: %d\n", sharedBuffer->wyjmij, buffer, getSemaphoreValue(semProd),  getSemaphoreValue(semCons));

        // Aktualizacja pozycji pobierania
        sharedBuffer->wyjmij = (sharedBuffer->wyjmij + 1) % NBUF;

        // Zwolnienie dostępu do bufora
        postSemaphore(semProd);

        if (buffer[0] == '\0') break; // Sygnał zakończenia danych

        // Zapis danych do pliku
        bytesWritten = write(outputFd, buffer, NELE);
        if (bytesWritten == -1)
        {
            perror("Błąd przy zapisie do pliku wyjściowego!");
            exit(EXIT_FAILURE);
        }

        sleep(rand() % (3 - 0 + 1) + 0); // losowo od 0 do 3 sec
    }

    close(outputFd);

    exit(EXIT_SUCCESS);
}