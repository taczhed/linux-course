#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define BUFFER_SIZE 24

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        printf("./a <plik_wejściowy> <plik_wyjściowy> <potok_nazwany>\n");
        exit(EXIT_FAILURE);
    }

    const char *inputFile = argv[1];
    const char *outputFile= argv[2];
    const char *namedPipe = argv[3];

    // Utworzenie potoku nazwanego
    if (mkfifo(namedPipe, 0666) == -1)
    {
        perror("Błąd w mkfifo");
        exit(EXIT_FAILURE);
    }

    pid_t producerPid, consumerPid;

    // Utworzenie procesu potomnego dla producenta
    producerPid = fork();
    if (producerPid == -1) {
        perror("Błąd w fork dla producenta");
        exit(EXIT_FAILURE);
    } else if (producerPid == 0) {
        execl("./execdir/producent.x", "./execdir/producent.x", namedPipe, inputFile, NULL);
        perror("Błąd w exec dla producenta");
        _exit(EXIT_FAILURE);
    }

    // Utworzenie procesu potomnego dla konsumenta
    consumerPid = fork();
    if (consumerPid == -1) {
        perror("Błąd w fork dla konsumenta");
        exit(EXIT_FAILURE);
    } else if (consumerPid == 0) {
        // Kod dla procesu potomnego konsumenta
        execl("./execdir/konsument.x", "./execdir/konsument.x", namedPipe, outputFile, NULL);
        perror("Błąd w exec dla konsumenta");
        _exit(EXIT_FAILURE);
    }

    // Oczekiwanie na zakończenie procesów potomnych
    int status;
    waitpid(producerPid, &status, 0);
    if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS) {
        printf("Proces producenta zakończony pomyślnie.\n");
    } else {
        printf("Proces producenta zakończony niepowodzeniem.\n");
    }

    waitpid(consumerPid, &status, 0);
    if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS) {
        printf("Proces konsumenta zakończony pomyślnie.\n");
    } else {
        printf("Proces konsumenta zakończony niepowodzeniem.\n");
    }

    // Usunięcie potoku nazwanego
    if (unlink(namedPipe) == -1) {
        perror("Błąd w unlink");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}