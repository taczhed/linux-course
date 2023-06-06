#include "pamiec_dzielona.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stddef.h>

int createSharedMemory(const char *name, size_t size)
{
    int shm_fd = shm_open(name, O_CREAT | O_RDWR | O_EXCL, S_IRUSR | S_IWUSR);
    if (shm_fd == -1)
    {
        perror("Błąd w shm_open()!");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(shm_fd, size) == -1)
    {
        perror("Błąd w ftruncate()!");
        exit(EXIT_FAILURE);
    }

    return shm_fd;
}

int openSharedMemory(const char *name)
{
    int shm_fd = shm_open(name, O_RDWR, S_IRUSR | S_IWUSR);
    if (shm_fd == -1)
    {
        perror("Błąd w shm_open()!");
        exit(EXIT_FAILURE);
    }
    return shm_fd;
}

void *mapSharedMemory(int shm_fd, size_t size)
{
    void *addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (addr == MAP_FAILED)
    {
        perror("Błąd w mmap()!");
        exit(EXIT_FAILURE);
    }
    return addr;
}

void closeSharedMemory(void *addr, size_t size)
{
    if (munmap(addr, size) == -1)
    {
        perror("Błąd w munmap()!");
        exit(EXIT_FAILURE);
    }
}

void removeSharedMemory(const char *name)
{
    if (shm_unlink(name) == -1)
    {
        perror("Błąd w shm_unlink()!");
        exit(EXIT_FAILURE);
    }
}