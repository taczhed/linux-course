#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define XMAX 45      // Maksymalna liczba kolumn ekranu
#define YMAX 20      // Maksymalna liczba wierszy ekranu

pthread_mutex_t mutex;
int sharedCounter = 0;

void gotoxy(unsigned x, unsigned y) {
    printf("\033[%d;%dH\033[2K", y, x);
}

void koniec(void) {
    printf("\n>>> Koniec procesu - porzadki zrobione!\n\n");
}

void *threadFunction(void *arg) {
    int threadNum = *(int *)arg;
    int numSections = *((int *)arg + 1);
    int privateCounter = 0;

    for (int i = 0; i < numSections; i++) {

        // Sekcja prywatna
        gotoxy(0, threadNum + 1);
        printf("Wątek %d, sekcja prywatna %d", threadNum, i + 1);
        fflush(stdout);
        sleep(rand() % (3 - 0 + 1) + 0); // losowo od 0 do 3 sec

        // Sekcja krytyczna
        pthread_mutex_lock(&mutex); // Blokowanie muteksu

        gotoxy(XMAX, threadNum + 1);
        printf("Wątek %d, sekcja krytyczna %d", threadNum, i + 1);
        fflush(stdout);

        privateCounter++;
        sharedCounter++;

        pthread_mutex_unlock(&mutex); // Odblokowanie muteksu

        sleep(rand() % (3 - 0 + 1) + 0); // losowo od 0 do 3 sec
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Podaj liczbę wątków i liczbę sekcji jako argumenty wywołania programu!\n");
        return 1;
    }

    int numThreads = atoi(argv[1]);
    int numSections = atoi(argv[2]);

    if (numThreads <= 0 || numSections <= 0) {
        printf("Podaj poprawne liczby wątków i sekcji!\n");
        return 1;
    }

    if (numSections > YMAX) {
        printf("Liczba sekcji przekracza maksymalną liczbę wierszy ekranu!\n");
        return 1;
    }

    if (numThreads > YMAX) {
        printf("Liczba wątków przekracza maksymalną liczbę wierszy ekranu!\n");
        return 1;
    }

    if (numThreads > 1 && numSections < 2) {
        printf("Jeśli liczba wątków jest większa niż 1, liczba sekcji musi być co najmniej 2!\n");
        return 1;
    }

    atexit(koniec);

    pthread_t *threads = malloc(numThreads * sizeof(pthread_t));
    int *threadArgs = malloc(numThreads * 2 * sizeof(int));

    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("Błąd przy init mutexu!");
        exit(EXIT_FAILURE);
    }

    printf("Adres muteksu: %p\n", &mutex);

    printf("\033[5;7m");     // Wlacz migotanie i odwrotny obraz
    printf("    ---- Nacisnij klawisz [Enter], aby wystartowac! ----   ");
    getchar();
    printf("\033[0m");       // Wroc do domyslnego trybu wyswietlania

    system("clear");

    srand(123);              // Zainicjuj generator liczb losowych
    printf("\033[1;4m");     // Wlacz pogrubienie i podkreslenie

    for (int i = 0; i < numThreads; i++) {
        threadArgs[i * 2] = i;
        threadArgs[i * 2 + 1] = numSections;
        if (pthread_create(&threads[i], NULL, threadFunction, &threadArgs[i * 2]) != 0) {
            perror("Error przy tworzeniu wątku!");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < numThreads; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Error przy podłączaniu się wątku!");
            exit(EXIT_FAILURE);
        }
    }

    pthread_mutex_destroy(&mutex);

    free(threads);
    free(threadArgs);

    printf("\033[0m");       // Wroc do domyslnego trybu wyswietlania
    gotoxy(0, YMAX+1);

    printf("Wartość licznika globalnego: %d\n", sharedCounter);
    printf("Oczekiwana wartość licznika globalnego: %d\n", numThreads * numSections);

    return 0;
}
