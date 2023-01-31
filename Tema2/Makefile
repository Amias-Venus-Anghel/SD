CC = gcc
CFLAGS = -Wall -g -std=c99

all: build

build: tema2

tema2: coada.o stiva.o lista.o netflix.o main.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: tema2.c netflix.h 
	$(CC) $(CFLAGS) -c $< -o $@

coada.o: coada.c coada.h coada_functii.h
	$(CC) $(CFLAGS) -c $< -o $@

stiva.o: stiva.c stiva.h stiva_functii.h
	$(CC) $(CFLAGS) -c $< -o $@
	
lista.o: lista.c lista.h
	$(CC) $(CFLAGS) -c $< -o $@

netflix.o: netflix.c netflix.h coada_functii.h stiva_functii.h lista.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean checkMem run

run: 
	./tema2 in_file out_file

clean:
	rm -f *.o main
	rm -f tema2

checkMem:
	valgrind --leak-check=yes --track-origins=yes ./tema2 in_file out_file

