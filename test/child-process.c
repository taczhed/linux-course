#include <stdio.h>
#include <unistd.h>

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
    print_process_info();
    return 0;
}
