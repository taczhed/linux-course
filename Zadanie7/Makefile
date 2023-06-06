CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -fPIC -pedantic
LDLIBS = -lrt -pthread

.PHONY: help
help:
	@echo "make all   		kompiluje programy"
	@echo "make run   		uruchamia program"
	@echo "make [bibloteka]-[typ]  tworzy bibloteke (semafor, pamiec), typu (static, shared)"
	@echo "make clean 		usuwa wszystkie pliki utworzone przez make"

.PHONY: run
run: main
	@./main ./input.txt ./output.txt

.PHONY: all
all: semafor.o pamiec_dzielona.o producent konsument main

main: ./src/main.c ./objdir/semafor.o ./objdir/pamiec_dzielona.o
	@$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

producent: ./src/producent.c ./objdir/semafor.o ./objdir/pamiec_dzielona.o
	@$(CC) $(CFLAGS) ./src/producent.c ./objdir/semafor.o ./objdir/pamiec_dzielona.o -o ./execdir/producent.x $(LDLIBS)

konsument: ./src/konsument.c ./objdir/semafor.o ./objdir/pamiec_dzielona.o
	@$(CC) $(CFLAGS) ./src/konsument.c ./objdir/semafor.o ./objdir/pamiec_dzielona.o -o ./execdir/konsument.x $(LDLIBS)

semafor.o: ./src/semafor.c ./src/semafor.h
	@$(CC) $(CFLAGS) -c ./src/semafor.c -o ./objdir/semafor.o $(LDLIBS)

pamiec_dzielona.o: ./src/pamiec_dzielona.c ./src/pamiec_dzielona.h
	@$(CC) $(CFLAGS) -c ./src/pamiec_dzielona.c -o ./objdir/pamiec_dzielona.o $(LDLIBS)

semafor-static: semafor.o
	ar rcs ./lib/semafor.a ./objdir/semafor.o

semafor-shared: semafor.o
	$(CC) -shared -o ./lib/semafor.so ./objdir/semafor.o

pamiec-static: pamiec_dzielona.o
	ar rcs ./lib/pamiec_dzielona.a ./objdir/pamiec_dzielona.o

pamiec-shared: pamiec_dzielona.o
	$(CC) -shared -o ./lib/pamiec_dzielona.so ./objdir/pamiec_dzielona.o

clean:
	@rm -f ./objdir/*.o ./execdir/*.x ./lib/*.a ./lib/*.so main