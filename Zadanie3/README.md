
# Ćwiczenie 3 - Wysyłanie sygnałów do procesów i ich obsługa.

Rozwiązania zadań ćwiczenia 3 z systemów operacyjnych.


## Struktura katalogów

Katalog główny zawiera pliki `Makefile` oraz `README.md`. Struktura opiera się o następujące podkatalogi:

- `/src`  - zawiera pliki źródłowe programów nazwane kolejnymi literami a-e,

- `/objdir`  - zawiera pliki obiektowe,

- `/execdir`  - zawiera pliki wykonywalne,

## Polecenia

| Komenda | Opis                     |
| :-------- | :-------------------------------- |
| `make`      | Uruchomienie pomocy |
| `make all`      | Kompiluje wszystkie programy |
| `make cw3x`      | Kompiluje program do ćwiczenia 3, podpunkt x, gdzie x = [a, b, c] |
| `make run-cw3x`      | make run-cw3x MODE=3 SINGAL=2	Uruchamia program (z przykładowymi danymi wejściowymi) do ćwiczenia 3, podpunkt x, gdzie x = [a, b, c], MODE to tryb programu (domyślnie 3), SINGAL to sygnał (domyślnie 2) |
| `make clean`      | Usuwa wszystkie pliki utworzone przez make |

## Autor

- Patryk Lach

