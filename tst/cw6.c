#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "library.h"


void onExit() {
    deleteSemaphore(SEMAPHORE_NAME);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Nieprawidłowe argumenty. Użyj: %s <nazwa_programu> <liczba_procesow> <liczba_sekcji_krytycznych>\n",
               argv[0]);
        return 1;
    }

    char *programName = argv[1];
    int numProcesses = atoi(argv[2]);
    int numSections = atoi(argv[3]);

    srand(getpid());
    signal(SIGINT, handleSignal);
    atexit(onExit);

    createOrUseExistingFile(FILE_NAME, 0);
    createSemaphore(SEMAPHORE_NAME, 1);

    for (int i = 0; i < numProcesses; ++i) {
        switch (fork()) {
            case -1:
                perror("Błąd tworzenia procesu potomnego");
                deleteSemaphore(SEMAPHORE_NAME);
                return 1;
            case 0:
                printf("Tworzenie procesu potomnego %d\n", getpid());
                execlp(programName, programName, argv[3], NULL);
                printf("Błąd uruchamiania procesu potomnego \n");
                _exit(EXIT_SUCCESS);
            default:
                break;

        }
    }

    for (int i = 0; i < numProcesses; ++i) {
        wait(NULL);
    }

    int file = openFile(FILE_NAME);
    int finalValue = readFileData(file);
    closeFile(file);

    if (finalValue == numProcesses * numSections) {
        printf("Poprawna końcowa wartość: %d\n", finalValue);
    } else {
        printf("Niezgodność w końcowej wartości: oczekiwano %d, otrzymano %d\n", numProcesses * numSections, finalValue);
    }

    return 0;
}
