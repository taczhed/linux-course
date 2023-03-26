#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
pid_t getpgid(pid_t pid);

int main() {

    printf("Zadanie 1 (d)\n");
    int pids[4];

    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork error");
            exit(-1);
        } else if (pid == 0) {
            sleep(3 - i);
            printf("Proces potomny: PID=%d PPID=%d UID=%d GID=%d PGID=%d\n", getpid(), getppid(), getuid(), getgid(), getpgid(0));
            exit(0);
        } else {
            pids[i] = pid;
        }
    }

    sleep(5);
    printf("Proces macierzysty: PID=%d PPID=%d UID=%d GID=%d PGID=%d\n\n", getpid(), getppid(), getuid(), getgid(), getpgid(0));
    printf("Drzewo zapisano do katalogu output/drzewo_genealogiczne.txt \n");

    FILE *fp;
    fp = fopen("../output/drzewo_genealogiczne.txt", "w");
    fprintf(fp, "~~~ PGID=%d ~~~\n\n(PID=%d, PPID=%d)───┬───(PID=%d, PPID=%d)\n                         ├───(PID=%d, PPID=%d)\n                         └───(PID=%d, PPID=%d)\n\n", getpgid(0), getpid(), getppid(), pids[0], getpid(), pids[1], getpid(), pids[2], getpid());
    fclose(fp);

    return 0;
}