
# Ćwiczenie 6 - Problem wzajemnego wykluczania procesów - semafory standardu POSIX.

Rozwiązania zadań ćwiczenia 6 z systemów operacyjnych.


## Struktura katalogów

Katalog główny zawiera pliki `Makefile` oraz `README.md`. Struktura opiera się o następujące podkatalogi:

- `/src`  - zawiera pliki źródłowe programów,

- `/objdir`  - zawiera pliki obiektowe,

- `/execdir`  - zawiera pliki wykonywalne,

## Polecenia

| Komenda | Opis                     |
| :-------- | :-------------------------------- |
| `make`      | Uruchomienie pomocy |
| `make all`      | Kompiluje programy |
| `make run PROCESY=2 SEKCJE=2`      | Uruchamia program z parametrami: PROCESY = liczba procesów,  SEKCJE = liczba sekcji |
| `make clean`      | Usuwa wszystkie pliki utworzone przez make |

## FAQ

#### Jaka będzie końcowa wartość numeru bez użycia sekcji krytycznej?

Dla 2 procesów oraz 2 sekcji z sekcją krytyczna wynik to 4.
Dla 2 procesów oraz 2 sekcji bez sekcji krytycznej wynik to 0.

## Autor

- Patryk Lach

