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
    char consumerBuffer[BUFFER_SIZE];
    ssize_t bytesRead, bytesWritten;

    // otwórz nazwany potok do odczytu
    pipefd = open(argv[1], O_RDONLY);
    if (pipefd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // otwórz plik wyjściowy
    int outputFd = open(argv[2], O_WRONLY);
    if (outputFd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // czytaj dane z potoku i zapisuj do pliku
    while ((bytesRead = read(pipefd, consumerBuffer, BUFFER_SIZE)) > 0) {
        if ((bytesWritten = write(outputFd, consumerBuffer, bytesRead)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        printf("Konsument otrzymał: %.*s\n", (int) bytesWritten, consumerBuffer);
        
        sleep(rand() % (3 - 0 + 1) + 0); // losowo od 0 do 3 sec
    }

    close(outputFd);
    close(pipefd);
    printf("Konsument zakończył pracę.\n");
    exit(EXIT_SUCCESS);
}