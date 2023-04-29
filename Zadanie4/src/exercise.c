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

    int pipefd[2];
    char producer_buffer[BUFFER_SIZE];
    char consumer_buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;
    pid_t pid;
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // otwórz plik wejściowy
    int input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // utwórz potok
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // rozdziel proces
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // Producent
    if (pid == 0)
    {
        close(pipefd[0]); // zamknij nieużywany koniec potoku

        // czytaj dane z pliku i zapisuj do potoku
        while ((bytes_read = read(input_fd, producer_buffer, BUFFER_SIZE)) > 0)
        {
            if (write(pipefd[1], producer_buffer, bytes_read) == -1)
            {
                perror("write");
                exit(EXIT_FAILURE);
            }
            printf("Producent wysłał: %s\n", producer_buffer);
            // losowe opóźnienie
            sleep(rand() % (3 - 0 + 1) + 0); // losowo od 0 do 3 sec
        }

        close(input_fd);  // zamknij plik wejściowy
        close(pipefd[1]); // zamknij koniec potoku
        exit(EXIT_SUCCESS);
    }

    // Konsument
    else
    {
        close(pipefd[1]); // zamknij nieużywany koniec potoku

        // otwórz plik wyjściowy
        int output_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC);
        if (output_fd == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }

        // czytaj dane z potoku i zapisuj do pliku
        while ((bytes_read = read(pipefd[0], consumer_buffer, BUFFER_SIZE)) > 0)
        {
            if ((bytes_written = write(output_fd, consumer_buffer, bytes_read)) == -1)
            {
                perror("write");
                exit(EXIT_FAILURE);
            }
            printf("Konsument otrzymał: %s\n", consumer_buffer);
            // losowe opóźnienie
            sleep(rand() % (3 - 0 + 1) + 0); // losowo od 0 do 3 sec
        }

        close(output_fd); // zamknij plik wyjściowy
        close(pipefd[0]); // zamknij koniec potoku
        printf("Konsument zakończył pracę.\n");
        exit(EXIT_SUCCESS);
    }

    return 0;
}