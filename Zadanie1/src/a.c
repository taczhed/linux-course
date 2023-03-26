#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
pid_t getpgid(pid_t pid);

int main () {

    printf("Zadanie 1 (a)\n");

    uid_t uid = getuid();   // identyfikator uzzytkownika (rzeczywisty)
    gid_t gid = getgid();   // identyfikator grupy uzzytkownika (rzeczywisty
    pid_t pid = getpid();   // identyfikator procesu
    pid_t ppid = getppid(); // identyfikator procesu macierzystego (przodka)
    pid_t pgid = getpgid(pid);  // identyfikator grupy procesow (lidera grupy)

    printf("UID: %d\n", uid);
    printf("GID: %d\n", gid);
    printf("PID: %d\n", pid);
    printf("PPID: %d\n", ppid);
    printf("PGID: %d\n", pgid);

    return 0;
}