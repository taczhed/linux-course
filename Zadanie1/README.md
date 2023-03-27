
# Ćwiczenie 1 - Procesy Potomne: fork

Rozwiązania zadań ćwiczenia 1 z systemów operacyjnych.


## Struktura katalogów

Katalog główny zawiera pliki `Makefile` oraz `README.md`. Struktura opiera się o następujące podkatalogi:

- `/src`  - zawiera pliki źródłowe programów nazwane kolejnymi literami a-e,

- `/objdir`  - zawiera pliki obiektowe,

- `/execdir`  - zawiera pliki wykonywalne,

- `/output`  - zawiera pliki wynikowe (drzewo programu `d.c`).


## Polecenia

| Komenda | Opis                     |
| :-------- | :-------------------------------- |
| `make`      | Uruchomienie pomocy |
| `make all`      | Kompilowanie wszystkich programów |
| `make cw1x`      | Kompilowanie programu do ćwiczenia 1, podpunkt x, gdzie x = [a, b, c, d, e] |
| `make run-cw1x`      | Uruchamianie programu do ćwiczenia 1, podpunkt x, gdzie x = [a, b, c, d, e] |
| `make clean`      | Usuwanie wszystkich plików utworzonych przez make |


## FAQ

#### Ile procesów powstanie przy n-krotnym wywołaniu funkcji fork i dlaczego?

Przy n-krotnym wywołaniu funkcji fork powstanie 2^n - 1 procesów. Funkcja fork() służy do tworzenia kopii bieżącego procesu w systemie operacyjnym. Gdy wywołujemy funkcję fork() raz, powstaje nowy proces potomny, który jest kopią procesu rodzica. Jeśli wywołamy funkcję fork() po raz drugi, to zarówno proces rodzic, jak i jego pierwszy proces potomny wywołają funkcję fork(), co spowoduje powstanie dwóch kolejnych procesów potomnych.


## Autor

- Patryk Lach

