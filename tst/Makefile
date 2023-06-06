cflags = -Wall -pedantic -std=c99
procesy = 3
sekcje = 3

all:
	gcc $(cflags) cw6.c library.c -o cw6.o -pthread && gcc $(cflags) potomny.c library.c -o potomny.o -pthread

zadanie6:
	gcc $(cflags) cw6.c library.c -o cw6.o -pthread && gcc $(cflags) potomny.c library.c -o potomny.o -pthread

run-zadanie6: zadanie6
	./cw6.o ./potomny.o $(procesy) $(sekcje)

clean:
	rm -f *.o *.a *.so
