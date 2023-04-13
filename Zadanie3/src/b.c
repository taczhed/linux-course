// #include <stdio.h>
// #include <stdlib.h>
// #include <signal.h>
// #include <unistd.h>
// #include <sys/wait.h>

// int main(int argc, char *argv[]) {

//     if (argc != 4) {
//         printf("Błąd wejścia\n");
//         return 1;
//     }

//     char* programName = argv[1];
//     int mode = atoi(argv[2]), signalNumber = atoi(argv[3]), status;

//     pid_t pid = fork();

//     if (pid < 0) {
//         printf("Błąd przy tworzeniu procesu potomnego\n");
//         return 1;
//     } else if (pid == 0) { // Proces potomny
//         execl(programName, programName, argv[2], argv[3], NULL);
//         printf("Błąd przy uruchamianiu programu\n");
//         exit(1);
//     } else { // Proces macierzysty

//         if (kill(pid, 0) == -1) {
//             printf("Proces potomny o PID %d nie istnieje\n", pid);
//             return 1;
//         }

//         sleep(1);

//         if (kill(pid, signalNumber) == -1) {
//             printf("Błąd podczas wysyłania sygnału do procesu potomnego\n");
//             return 1;
//         }

//         wait(&status);

//         if (WIFSIGNALED(status)) {
//             printf("Proces potomny o PID %d został zakończony przez sygnał: %d - %s\n", pid, WTERMSIG(status), strsignal(WTERMSIG(status)));
//         } else {
//             printf("Proces potomny o PID %d zakończył się normalnie\n", pid);
//         }

//         printf("Status zakończenia: %d\n", status);
//     }

//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    int mode = 1, signalNumber = 3, pid, status;

    printf("Podaj tryb pracy (1 - akcja domyślna, 2 - ignorowanie, 3 - własna obsługa): ");
    scanf("%d", &mode);

    printf("Podaj numer sygnału do obsługi: ");
    scanf("%d", &signalNumber);

    pid = fork();

    if (pid < 0) {
        printf("Błąd podczas tworzenia procesu potomnego\n");
        return 1;
    }

    else if (pid == 0) {

        char arg1[2], arg2[2];
        sprintf(arg1, "%d", mode);
        sprintf(arg2, "%d", signalNumber);
        execlp("./a", "./a", arg1, arg2, NULL);
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
