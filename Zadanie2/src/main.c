#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// ./main ./execProg

pid_t getpgid(pid_t pid);

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Brak programu do uruchomienia przez procesy!\n");
        exit(-1);
    }

    printf("Zadanie 2\n");
    printf("Proces macierzysty: PID=%d PPID=%d UID=%d GID=%d PGID=%d\n", getpid(), getppid(), getuid(), getgid(), getpgid(0));

    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork error");
            exit(-1);
        } else if (pid == 0) {
            execlp(argv[1], argv[1], NULL);
            perror("exec error");
            exit(-1);
        } else {
            wait(NULL);
        }
    }

    return 0;
}