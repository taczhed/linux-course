CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99

all: cw2

cw2: cw2.c
	$(CC) $(CFLAGS) cw2.c -o cw2 && $(CC) $(CFLAGS) child-process.c -o child-process

run-cw2: cw2
	./cw2

clean:
	rm -f cw2 child-process
