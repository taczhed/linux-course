#include <stddef.h>

#ifndef PAMIEC_DZIELONA_H
#define PAMIEC_DZIELONA_H

#define NELE 2 // Rozmiar elementu bufora (jednostki towaru) w bajtach
#define NBUF 3 // Liczba elementów bufora

typedef struct
{
    char bufor[NBUF][NELE];
    int wstaw, wyjmij;
} SegmentPD;

int createSharedMemory(const char *name, size_t size);
int openSharedMemory(const char *name);
void *mapSharedMemory(int shm_fd, size_t size);
void closeSharedMemory(void *addr, size_t size);
void removeSharedMemory(const char *name);

#endif  /* PAMIEC_DZIELONA_H */