#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void print_process_info() {
    uid_t uid = getuid();
    gid_t gid = getgid();
    pid_t pid = getpid();
    pid_t ppid = getppid();
    gid_t pgid = getpgid(pid);

    printf("UID: %d \n", uid);
    printf("GID: %d \n", gid);
    printf("PID: %d \n", pid);
    printf("PPID: %d \n", ppid);
    printf("PGID: %d \n", pgid);
}

int main() {
    printf("Parent process info: \n");
    print_process_info();

    for (int i = 0; i < 3; i++) {
        switch (fork()) {
            case -1:
                perror("fork");
                exit(EXIT_FAILURE);
            case 0:
                printf("Child process info: \n");
                execlp("./child-process", "./child-process", NULL);
                perror("execlp() error");
                exit(EXIT_SUCCESS);
            default:
                wait(NULL);
                break;
        }
    }

    return 0;
}
