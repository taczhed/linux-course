CC = gcc
CFLAGS = -Wall -Wextra
SRC_DIR = src
OBJ_DIR = objdir
EXEC_DIR = execdir

all: client server

help:
	@echo "make all		kompiluje programy"
	@echo "make client		kompiluje plik klienta"
	@echo "make server		kompiluje plik serwera"
	@echo "make run-[server]    	uruchamia (server, client)"
	@echo "make clean 		usuwa wszystkie pliki utworzone przez make"

client: $(OBJ_DIR)/client.o 
	$(CC) $(CFLAGS) -o $(EXEC_DIR)/client $(OBJ_DIR)/client.o -lrt

server: $(OBJ_DIR)/server.o
	$(CC) $(CFLAGS) -o $(EXEC_DIR)/server $(OBJ_DIR)/server.o -lrt

$(OBJ_DIR)/client.o: $(SRC_DIR)/client.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/client.c -o $(OBJ_DIR)/client.o -lrt

$(OBJ_DIR)/server.o: $(SRC_DIR)/server.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/server.c -o $(OBJ_DIR)/server.o -lrt

run-client:
	@./execdir/client

run-server:
	@./execdir/server

clean:
	rm -f $(EXEC_DIR)/client $(EXEC_DIR)/server $(OBJ_DIR)/*.o