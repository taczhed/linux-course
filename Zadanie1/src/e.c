#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
pid_t getpgid(pid_t pid);

int main() {

    printf("Zadanie 1 (e)\n");

    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork error");
            exit(-1);
        } else if (pid == 0) {
            setpgid(0, 0);
            printf("Proces potomny: PID=%d PPID=%d UID=%d GID=%d PGID=%d\n", getpid(), getppid(), getuid(), getgid(), getpgid(0));
            exit(0);
        }
    }

    printf("Proces macierzysty: PID=%d PPID=%d UID=%d GID=%d PGID=%d\n", getpid(), getppid(), getuid(), getgid(), getpgid(0));

    return 0;
}