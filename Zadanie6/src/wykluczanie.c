#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <semaphore.h>
#include <time.h>

sem_t *sem; // Deklaracja wskaźnika na semafor

void critical_section(int process_id, int section_id) {
    int fd = open("numer.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    char read_buf[10];
    read(fd, read_buf, sizeof(read_buf));
    int current_number = atoi(read_buf);
    int new_number = current_number + 1;

    lseek(fd, 0, SEEK_SET);
    char num_str[10];
    sprintf(num_str, "%d", new_number);
    write(fd, num_str, strlen(num_str));

    close(fd);

    printf("Proces %d - Sekcja krytyczna %d: Obecna liczba = %d, Nowa liczba = %d\n", process_id, section_id, current_number, new_number);

    srand(time(NULL));
    int sleep_time = rand() % 5 + 1;
    sleep(sleep_time);

    printf("Proces %d - Sekcja krytyczna %d: Wychodzenie z sekcji krytycznej\n", process_id, section_id);
}

int main() {
    sem = sem_open("/semaphore", 0); // Otwarcie semafora

    if (sem == SEM_FAILED) {
        perror("sem_open");
        return 1;
    }

    int process_id = getpid();
    srand(process_id);

    int num_sections = 3;
    int section_id;

    for (section_id = 0; section_id < num_sections; section_id++) {
        sem_wait(sem); // Zajęcie semafora
        printf("Proces %d - Sekcja krytyczna %d: Wchodzenie do sekcji krytycznej\n", process_id, section_id);
        critical_section(process_id, section_id);
        sem_post(sem); // Zwolnienie semafora
    }

    sem_close(sem); // Zamknięcie semafora

    return 0;
}