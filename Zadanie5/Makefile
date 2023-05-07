# Definicja zmiennych
CC = gcc
CFLAGS = -pedantic -Wall -std=c99

SRC_DIR = src
OBJ_DIR = objdir
EXEC_DIR = execdir

FILE = a
PRODUCENT = producent
KONSUMENT = konsument
POTOK = testpotok

.PHONY: help
help:
	@echo "make all		kompiluje programy"
	@echo "make run-cw5a POTOK=test		uruchamia program a z nazwą potoku"
	@echo "make clean		usuwa wszystkie pliki utworzone przez make"

# budowanie wszystkich plików
.PHONY: all
all: $(EXEC_DIR)/${FILE}.x $(EXEC_DIR)/${PRODUCENT}.x $(EXEC_DIR)/${KONSUMENT}.x

# uruchamianie programu
.PHONY: run-cw5a
run-cw5a: $(EXEC_DIR)/$(FILE).x
	@./$(EXEC_DIR)/$(FILE).x ./$(SRC_DIR)/input.txt ./$(SRC_DIR)/output.txt $(POTOK)

# reguła dla pliku obiektowego
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# reguła dla pliku wykonywalnego
$(EXEC_DIR)/%.x: $(OBJ_DIR)/%.o
	@$(CC) $(CFLAGS) $< -o $@
	
# czyszczenie
clean:
	@rm -f $(OBJ_DIR)/*.o $(EXEC_DIR)/*.x output/*