CC = gcc
CFLAGS = -Wall -g -std=c99

all: build

build: tema3

tema3: trie.o main.o carte.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: tema3.c trie.h carte.h
	$(CC) $(CFLAGS) -c $< -o $@

trie.o: trie.c trie.h
	$(CC) $(CFLAGS) -c $< -o $@

carte.o: carte.c carte.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f *.o main tema3



