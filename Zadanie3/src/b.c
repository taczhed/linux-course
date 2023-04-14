#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[])
{

    if (argc != 4) {
        printf("Błąd wejścia\n");
        return 1;
    }

    int mode, signalNumber, pid, status;

    sscanf(argv[2], "%d", &mode);
    sscanf(argv[3], "%d", &signalNumber);

    pid = fork();

    if (pid < 0) {
        printf("Błąd podczas tworzenia procesu potomnego\n");
        return 1;
    }

    else if (pid == 0) {
        execlp(argv[1], argv[1], argv[2], argv[3], NULL);
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
