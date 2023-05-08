#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <signal.h>

#define NUM_PROCESSES 5
#define NUM_SECTIONS 3

sem_t *sem; // Deklaracja wskaźnika na semafor

// Funkcja obsługująca wyjście z programu
void exit_handler() {
    sem_unlink("/semaphore"); // Usunięcie semafora
}

// Funkcja obsługująca sygnał SIGINT (Ctrl+C)
void sigint_handler(int signum) {
    exit(0); // Zakończenie programu
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Użycie: %s <program> <liczba procesow> <liczba sekcji>\n", argv[0]);
        return 1;
    }

    char *program_name = argv[1];
    int num_processes = atoi(argv[2]);
    int num_sections = atoi(argv[3]);

    sem = sem_open("/semaphore", O_CREAT | O_EXCL, 0666, 1); // Tworzenie i inicjalizacja semafora
    if (sem == SEM_FAILED) {
        perror("sem_open");
        return 1;
    }

    atexit(exit_handler); // Rejestrowanie funkcji obsługi wyjścia z programu
    signal(SIGINT, sigint_handler); // Rejestrowanie funkcji obsługi sygnału SIGINT

    int fd = open("numer.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char num_str[10];
    sprintf(num_str, "%d", 0);
    write(fd, num_str, strlen(num_str));
    close(fd);

    int i;
    for (i = 0; i < num_processes; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            execlp(program_name, program_name, NULL); // Uruchomienie programu realizującego wzajemne wykluczanie
            perror("execlp");
            return 1;
        } else if (pid < 0) {
            perror("fork");
            return 1;
        }
    }

    for (i = 0; i < num_processes; i++) {
        wait(NULL); // Oczekiwanie na zakończenie wszystkich procesów potomnych
    }

    fd = open("numer.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char read_buf[10];
    read(fd, read_buf, sizeof(read_buf));
    int final_number = atoi(read_buf);

    printf("Końcowy numer: %d\n", final_number);

    close(fd);
    sem_close(sem); // Zamknięcie semafora
    sem_unlink("/semaphore"); // Usunięcie semafora

    return 0;
}