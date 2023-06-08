CC = gcc
CFLAGS = -Wall -Wextra
SRC_DIR = src
OBJ_DIR = objdir
EXEC_DIR = execdir

THREADS = 4
SECTIONS = 5

all: main

help:
	@echo "make all		kompiluje program"
	@echo "make run THREADS=4 SECTIONS=5  	uruchamia program z parmetrami (THREADS -> wątki, SECTIONS -> sekcje)"
	@echo "make clean 		usuwa wszystkie pliki utworzone przez make"

main: $(OBJ_DIR)/main.o 
	@$(CC) $(CFLAGS) -o $(EXEC_DIR)/main $(OBJ_DIR)/main.o -lrt

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o -lrt

run:
	@./execdir/main $(THREADS) $(SECTIONS)

clean:
	rm -f $(EXEC_DIR)/main $(OBJ_DIR)/*.o