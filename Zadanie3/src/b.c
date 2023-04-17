#define _POSIX_C_SOURCE 200112L
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[])
{

    if (argc != 3) {
        printf("Błąd wejścia\n");
        return 1;
    }

    int mode, signalNumber, pid, status;

    sscanf(argv[1], "%d", &mode);
    sscanf(argv[2], "%d", &signalNumber);

    printf("Uruchomiono b.c, PID: %d, tryb: %d, sygnał: %d\n", getpid(), mode, signalNumber);

    pid = fork();

    if (pid < 0) {
        printf("Błąd podczas tworzenia procesu potomnego\n");
        return 1;
    }

    else if (pid == 0) {
        execlp("./execdir/a.x", "./execdir/a.x", argv[1], argv[2], NULL);
        printf("Błąd przy uruchamianiu programu!\n");
        exit(1);
    }

    else {
        if (kill(pid, 0) == -1) {
            printf("Proces potomny o PID %d nie istnieje\n", pid);
            return 1;
        }

        sleep(1);

        if (kill(pid, signalNumber) == -1) {
            printf("Błąd podczas wysyłania sygnału do procesu potomnego\n");
            return 1;
        }

        wait(&status);

        if (WIFSIGNALED(status)) {
            printf("Proces potomny o PID %d został zakończony przez sygnał: %d - %s\n", pid, WTERMSIG(status), strsignal(WTERMSIG(status)));
        }
        
        else {
            printf("Proces potomny o PID %d zakończył się normalnie\n", pid);
        }

        printf("Status zakończenia: %d\n", status);
    }

    return 0;
}
