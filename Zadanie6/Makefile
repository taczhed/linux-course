# Definicja zmiennych
CC = gcc
CFLAGS = -pedantic -Wall -std=c99

SRC_DIR = src
OBJ_DIR = objdir
EXEC_DIR = execdir

PROCESY = 2
SEKCJE = 2

.PHONY: help
help:
	@echo "make all		kompiluje programy"
	@echo "make run PROCESY=2 SEKCJE=2		uruchamia program z parametrami: PROCESY = liczba procesów,  SEKCJE = liczba sekcji"
	@echo "make clean		usuwa wszystkie pliki utworzone przez make"

# budowanie wszystkich plików
.PHONY: all
all: $(EXEC_DIR)/powielacz.x $(EXEC_DIR)/wykluczanie.x

# uruchamianie programu
.PHONY: run
run: $(EXEC_DIR)/powielacz.x
	@./$(EXEC_DIR)/powielacz.x ./$(EXEC_DIR)/wykluczanie.x $(PROCESY) $(SEKCJE)

# reguła dla pliku obiektowego
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -pthread

# reguła dla pliku wykonywalnego
$(EXEC_DIR)/%.x: $(OBJ_DIR)/%.o
	@$(CC) $(CFLAGS) $< -o $@ -pthread
	
# czyszczenie
clean:
	@rm -f $(OBJ_DIR)/*.o $(EXEC_DIR)/*.x output/*