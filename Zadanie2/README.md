
# Ćwiczenie 2 - Tworzenie procesów potomnych i uruchamianie w nich nowego programu

Rozwiązania zadań ćwiczenia 2 z systemów operacyjnych.


## Struktura katalogów

Katalog główny zawiera pliki `Makefile` oraz `README.md`. Struktura opiera się o następujące podkatalogi:

- `/src`  - zawiera pliki źródłowe programów,

- `/objdir`  - zawiera pliki obiektowe,

- `/execdir`  - zawiera pliki wykonywalne,

## Polecenia

| Komenda | Opis                     |
| :-------- | :-------------------------------- |
| `make`      | Uruchamia pomocy |
| `make all`      | Kompiluje główny program i od niego zależny |
| `make cw2`      | Kompiluje program do ćwiczenia 2 |
| `make cw2-child`      | Kompiluje program zależny dla programu głównego |
| `make run-cw2`      | Uruchamia program do ćwiczenia 2 |
| `make clean`      | Usuwa wszystkie pliki utworzone przez make |


## FAQ

#### Ile procesów powstanie przy n-krotnym wywołaniu funkcji `fork-exec` jak wyżej i dlaczego?

Każde wywołanie funkcji fork tworzy kopię procesu rodzica. Gdy proces potomny wykonuje funkcję exec, to pamięć i kod źródłowy procesu potomnego zostaje zastąpiony przez nowy program. Następne wywołanie fork tworzy kopię procesu potomnego z już zmienioną pamięcią i kodem źródłowym, które zostały zmienione przez wcześniejsze wywołanie exec.

Dlatego, każde kolejne wywołanie exec wewnątrz funkcji fork spowoduje utworzenie kolejnego procesu potomnego z zastąpionym kodem źródłowym i pamięcią, a to oznacza, że liczba procesów potomnych utworzonych przez n-krotne wywołanie funkcji exec wewnątrz funkcji fork będzie wynosić n plus proces macierzysty.


## Autor

- Patryk Lach

