#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sig_handler(int signalNumber) {
    printf("Przechwycono sygnał nr %d --> własna obsługa sygnału\n", signalNumber);
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Błąd wejścia\n");
        return 1;
    }

    int mode = atoi(argv[1]);
    int signalNumber = atoi(argv[2]);
    
    printf("Uruchomiono a.c, PID: %d, tryb: %d, sygnał: %d\n", getpid(), mode, signalNumber);

    if (mode == 1) {

        if (signal(signalNumber, SIG_DFL) == SIG_ERR) {
            printf("Błąd!\n");
            return 1; 
        }
    
        printf("Oczekiwanie na sygnał...\n");
        pause();
    }

    if (mode == 2) {

        if (signal(signalNumber, SIG_IGN) == SIG_ERR) {
            printf("Błąd!\n");
            return 1;
        }
        printf("Oczekiwanie na sygnał...\n");
        pause();
    }
    
    if (mode == 3) {

        if (signal(signalNumber, sig_handler) == SIG_ERR) {
            printf("Błąd!\n");
            return 1;
        }
        printf("Oczekiwanie na sygnał...\n");
        pause();
    }

    return 0;
}