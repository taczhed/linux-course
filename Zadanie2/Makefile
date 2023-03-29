# Definicja zmiennych
CC = gcc
CFLAGS = -pedantic -Wall -std=c99

SRC_DIR = src
OBJ_DIR = objdir
EXEC_DIR = execdir

.PHONY: help
help:
	@echo "make all		Kompiluje główny program i od niego zależny"
	@echo "make cw2	Kompiluje program do ćwiczenia 2"
	@echo "make cw2-child	Kompiluje program zależny dla programu głównego"
	@echo "make run-cw2	Uruchamia program do ćwiczenia 2"
	@echo "make clean		Usuwa wszystkie pliki utworzone przez make"

# budowanie wszystkich plików
.PHONY: all
all: $(EXEC_DIR)/main.x $(EXEC_DIR)/child.x

# budowanie pojedynczego pliku
.PHONY: cw2
cw2: $(EXEC_DIR)/main.x

.PHONY: cw2-child
cw2-child: $(EXEC_DIR)/child.x

# uruchamianie pojedynczego pliku
.PHONY: run-cw2
run-cw2: $(EXEC_DIR)/main.x
	@./$(EXEC_DIR)/main.x ./$(EXEC_DIR)/child.x

# reguła dla pliku obiektowego
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# reguła dla pliku wykonywalnego
$(EXEC_DIR)/%.x: $(OBJ_DIR)/%.o
	@$(CC) $(CFLAGS) $< -o $@
	
# czyszczenie
clean:
	@rm -f $(OBJ_DIR)/*.o $(EXEC_DIR)/*.x