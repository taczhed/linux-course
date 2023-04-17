# Definicja zmiennych
CC = gcc
CFLAGS = -pedantic -Wall -std=c99

SRC_DIR = src
OBJ_DIR = objdir
EXEC_DIR = execdir

FILE_A = a
FILE_B = b
FILE_C = c
FILE_C1 = c1

MODE = 3
SIGNAL = 2

.PHONY: help
help:
	@echo "make all		Kompiluje wszystkie programy"
	@echo "make cw3x	Kompiluje program do ćwiczenia 3, podpunkt x, gdzie x = [a, b, c]"
	@echo "make run-cw3x MODE=3 SINGAL=2	Uruchamia program (z przykładowymi danymi wejściowymi) do ćwiczenia 3, podpunkt x, gdzie x = [a, b, c], MODE to tryb programu (domyślnie 3), SINGAL to sygnał (domyślnie 2)"
	@echo "make clean		Usuwa wszystkie pliki utworzone przez make"

# budowanie wszystkich plików
.PHONY: all
all: $(EXEC_DIR)/${FILE_A}.x $(EXEC_DIR)/${FILE_B}.x $(EXEC_DIR)/${FILE_C}.x $(EXEC_DIR)/${FILE_C1}.x

# budowanie pojedynczego pliku
.PHONY: cw3$(FILE_A) cw3$(FILE_B) cw3$(FILE_C)
cw3$(FILE_A): $(EXEC_DIR)/${FILE_A}.x

cw3$(FILE_B): $(EXEC_DIR)/${FILE_B}.x

cw3$(FILE_C): $(EXEC_DIR)/$(FILE_C).x $(EXEC_DIR)/$(FILE_C1).x

# uruchamianie pojedynczego pliku
.PHONY: run-cw3$(FILE_A) run-cw3$(FILE_B) run-cw3$(FILE_C)
run-cw3$(FILE_A): $(EXEC_DIR)/$(FILE_A).x
	@./$(EXEC_DIR)/$(FILE_A).x ${MODE} ${SIGNAL}

run-cw3$(FILE_B): $(EXEC_DIR)/$(FILE_B).x
	@./$(EXEC_DIR)/$(FILE_B).x ${MODE} ${SIGNAL}

run-cw3$(FILE_C): $(EXEC_DIR)/$(FILE_C).x
	@./$(EXEC_DIR)/$(FILE_C).x ${MODE} ${SIGNAL}

# reguła dla pliku obiektowego
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# reguła dla pliku wykonywalnego
$(EXEC_DIR)/%.x: $(OBJ_DIR)/%.o
	@$(CC) $(CFLAGS) $< -o $@
	
# czyszczenie
clean:
	@rm -f $(OBJ_DIR)/*.o $(EXEC_DIR)/*.x output/*