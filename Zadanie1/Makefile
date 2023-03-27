# Definicja zmiennych
CC = gcc
CFLAGS = -pedantic -Wall -std=c99

SRC_DIR = src
OBJ_DIR = objdir
EXEC_DIR = execdir

FILE_A = a
FILE_B = b
FILE_C = c
FILE_D = d
FILE_E = e

.PHONY: help
help:
	@echo "make all		kompiluje wszystkie programy"
	@echo "make cw1x	kompiluje program do ćwiczenia 1, podpunkt x, gdzie x = [a, b, c, d, e]"
	@echo "make run-cw1x	uruchamia program do ćwiczenia 1, podpunkt x, gdzie x = [a, b, c, d, e]"
	@echo "make clean		usuwa wszystkie pliki utworzone przez make"

# budowanie wszystkich plików
.PHONY: all
all: $(EXEC_DIR)/${FILE_A}.x $(EXEC_DIR)/${FILE_B}.x $(EXEC_DIR)/${FILE_C}.x $(EXEC_DIR)/${FILE_D}.x $(EXEC_DIR)/${FILE_E}.x

# budowanie pojedynczego pliku
.PHONY: cw1$(FILE_A) cw1$(FILE_B) cw1$(FILE_C) cw1$(FILE_D) cw1$(FILE_E)
cw1$(FILE_A): $(EXEC_DIR)/${FILE_A}.x

cw1$(FILE_B): $(EXEC_DIR)/${FILE_B}.x

cw1$(FILE_C): $(EXEC_DIR)/$(FILE_C).x

cw1$(FILE_D): $(EXEC_DIR)/$(FILE_D).x

cw1$(FILE_E): $(EXEC_DIR)/$(FILE_E).x

# uruchamianie pojedynczego pliku
.PHONY: run-cw1$(FILE_A) run-cw1$(FILE_B) run-cw1$(FILE_C) run-cw1$(FILE_D) run-cw1$(FILE_E)
run-cw1$(FILE_A): $(EXEC_DIR)/$(FILE_A).x
	@./$(EXEC_DIR)/$(FILE_A).x

run-cw1$(FILE_B): $(EXEC_DIR)/$(FILE_B).x
	@./$(EXEC_DIR)/$(FILE_B).x

run-cw1$(FILE_C): $(EXEC_DIR)/$(FILE_C).x
	@./$(EXEC_DIR)/$(FILE_C).x

run-cw1$(FILE_D): $(EXEC_DIR)/$(FILE_D).x
	@./$(EXEC_DIR)/$(FILE_D).x

run-cw1$(FILE_E): $(EXEC_DIR)/$(FILE_E).x
	@./$(EXEC_DIR)/$(FILE_E).x

# reguła dla pliku obiektowego
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# reguła dla pliku wykonywalnego
$(EXEC_DIR)/%.x: $(OBJ_DIR)/%.o
	@$(CC) $(CFLAGS) $< -o $@
	
# czyszczenie
clean:
	@rm -f $(OBJ_DIR)/*.o $(EXEC_DIR)/*.x output/*