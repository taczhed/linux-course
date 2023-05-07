#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#define BUFFER_SIZE 24

int main(int argc, char **argv)
{
    srand(time(NULL));

    int pipefd;
    char producerBuffer[BUFFER_SIZE];
    ssize_t bytesRead, bytesWritten;

    // otwórz nazwany potok do zapisu
    pipefd = open(argv[1], O_WRONLY);
    if (pipefd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // otwórz plik wejściowy
    int inputFd = open(argv[2], O_RDONLY);
    if (inputFd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // czytaj dane z pliku i zapisuj do potoku
    while ((bytesRead = read(inputFd, producerBuffer, BUFFER_SIZE)) > 0)
    {
        if ((bytesWritten = write(pipefd, producerBuffer, bytesRead)) == -1)
        {
            perror("write");
            exit(EXIT_FAILURE);
        }
        printf("Producent wysłał: %.*s\n", (int) bytesWritten, producerBuffer);
        
        sleep(rand() % (3 - 0 + 1) + 0); // losowo od 0 do 3 sec
    }

    close(inputFd);
    close(pipefd);
    exit(EXIT_SUCCESS);
}