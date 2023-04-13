#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sig_handler(int signalNumber) {
    printf("Przechwycono sygnał nr %d\n", signalNumber);
    printf("Własna obsługa sygnału\n");
}

// Tryby (parametr pierwszy): 
// - 1 - akcja domyślna, 
// - 2 - ignorowanie,
// - 3 - własna obsługa

// Numer sygnału (parametr drugi): np. 2, 15 itd

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Błąd wejścia\n");
        return 1;
    }

    int mode = atoi(argv[1]);
    int signalNumber = atoi(argv[2]);
    
    printf("Tryb: %d, sygnał: %d\n", mode, signalNumber);
    printf("PID to %d\n", getpid());

    if (mode == 1) {

        if (signal(signalNumber, SIG_DFL) == SIG_ERR) {
            printf("Błąd!\n");
            return 1; 
        }
    
        printf("Oczekiwanie na sygnał\n");
        pause();
    }

    if (mode == 2) {

        if (signal(signalNumber, SIG_IGN) == SIG_ERR) {
            printf("Błąd!\n");
            return 1;
        }
        printf("Oczekiwanie na sygnał\n");
        pause();
    }
    
    if (mode == 3) {

        if (signal(signalNumber, sig_handler) == SIG_ERR) {
            printf("Błąd!\n");
            return 1;
        }
        printf("Oczekiwanie na sygnał\n");
        pause();
    }

    return 0;
}