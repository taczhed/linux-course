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
	@echo "make all		Kompiluje wszystkie programy"
	@echo "make run-all		Uruchamia wszystkie programy"
	@echo "make run-a	Uruchamia program a (w miejsce a można wstawić nazwę dowolnego programu a-e)"
	@echo "make clean		Usuwa pliki *.o oraz *.x"

# budowanie wszystkich plików
.PHONY: all
all: $(EXEC_DIR)/${FILE_A}.x $(EXEC_DIR)/${FILE_B}.x $(EXEC_DIR)/${FILE_C}.x $(EXEC_DIR)/${FILE_D}.x $(EXEC_DIR)/${FILE_E}.x

# uruchamianie wszystkich plików
.PHONY: run-all
run-all: $(EXEC_DIR)/$(FILE_A).x $(EXEC_DIR)/$(FILE_B).x $(EXEC_DIR)/$(FILE_C).x $(EXEC_DIR)/$(FILE_E).x $(EXEC_DIR)/$(FILE_D).x
		@./$(EXEC_DIR)/$(FILE_A).x
		@./$(EXEC_DIR)/$(FILE_B).x
		@./$(EXEC_DIR)/$(FILE_C).x
		@./$(EXEC_DIR)/$(FILE_E).x
		@./$(EXEC_DIR)/$(FILE_D).x

# budowanie wszystkich plików
.PHONY: run-$(FILE_A) run-$(FILE_B)
run-$(FILE_A): $(EXEC_DIR)/$(FILE_A).x
	@./$(EXEC_DIR)/$(FILE_A).x

run-$(FILE_B): $(EXEC_DIR)/$(FILE_B).x
	@./$(EXEC_DIR)/$(FILE_B).x

run-$(FILE_C): $(EXEC_DIR)/$(FILE_C).x
	@./$(EXEC_DIR)/$(FILE_C).x

run-$(FILE_D): $(EXEC_DIR)/$(FILE_D).x
	@./$(EXEC_DIR)/$(FILE_D).x

run-$(FILE_E): $(EXEC_DIR)/$(FILE_E).x
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