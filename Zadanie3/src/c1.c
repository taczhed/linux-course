#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Błąd wejścia\n");
        return 1;
    }

    pid_t pid;
    int mode, signalNumber, status, subTasks = 3;

    sscanf(argv[1], "%d", &mode);
    sscanf(argv[2], "%d", &signalNumber);

    printf("Uruchomiono c1, PID: %d, tryb: %d, sygnał: %d\n", getpid(), mode, signalNumber);

    signal(signalNumber, SIG_IGN); // Ignorowanie sygnału

    // Stanie się liderem grupy procesów
    pid = getpid();
    setpgid(pid, pid);

    printf("Liderem stał się %d\n", pid);

    // Tworzenie kilku procesów potomnych
    for (int i = 0; i < subTasks; i++) {
        pid = fork();
        if (pid == 0) {
            execl("./execdir/a.x", "./execdir/a.x", argv[1], argv[2], NULL);
            exit(1);
        }
    }

    // Oczekiwanie na zakończenie procesów potomnych
    for (int i = 0; i < subTasks; i++) {
        pid = wait(&status);
        if (WIFEXITED(status)) {
            printf("Proces potomny o PID %d zakończył działanie ze statusem: %d\n", pid, WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status)) {
            printf("Proces potomny o PID %d zakończył działanie przez sygnał: %d\n", pid, WTERMSIG(status));
        }
    }

    return 0;
}