
# Ćwiczenie 7 - Problem producenta-konsumenta z buforem cyklicznym - pamięć dzielona i semafory standardu POSIX.

Rozwiązania zadań ćwiczenia 7 z systemów operacyjnych.


## Struktura katalogów

Katalog główny zawiera pliki `Makefile` oraz `README.md`. Struktura opiera się o następujące podkatalogi:

- `/src`  - zawiera pliki źródłowe programów,

- `/objdir`  - zawiera pliki obiektowe,

- `/execdir`  - zawiera pliki wykonywalne,

- `/lib`  - zawiera pliki biblotek,

## Polecenia

| Komenda | Opis                     |
| :-------- | :-------------------------------- |
| `make`      | Uruchomienie pomocy |
| `make all`      | Kompiluje wszystkie programy |
| `make [bibloteka]-[typ]`      | Tworzy bibloteke (semafor, pamiec), typu (static, shared) |
| `make run-[typ]`      | Uruchamia program w typie (default, static, dlopen, dlsym) |
| `make clean`      | Usuwa wszystkie pliki utworzone przez make |


## Autor

- Patryk Lach

