CC = gcc
CFLAGS = -std=c99 -Wall
LDFLAGS = -lm -lrt

all: server client

server: server.c common.h
	$(CC) $(CFLAGS) server.c -o server $(LDFLAGS)

client: client.c common.h
	$(CC) $(CFLAGS) client.c -o client $(LDFLAGS)

clean:
	rm -f server client