/* ANGHEL Ionela-Carmen - 312CB */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

#define ALPHABET_SIZE (68)

/* structura trie */
typedef struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE+1]; /* vector de copii */
    bool isEndOfWord; /* true daca e sfarsit de cuvant, false altfel */
    void* info; /* informatia generalizata */
}Trie, *ATrie;

typedef int (*TCmp)(char); /* functie de calculare a indexului */
typedef void (*Tfr)(void*); /* functie de eliberare a informatiei */
typedef void (*Tafi)(void*, FILE* fout); /* fct de afisare */

/* FUNCTII */
ATrie GetNode(); /* initializeaza nod de arbore nou */
void Insert(ATrie root, char *key, TCmp idx, void* info); /* insereaza in arbore */
void* Get(ATrie root, char* key, TCmp idx); /* returneaza adresa informatiei daca exista */
void FreeTrie(ATrie root, Tfr fr); /* eliberare memorie alocata */
void free_all(ATrie root); /* elibereaza un Trie fara informatii */
void AfiTrie(ATrie root, Tafi afi, FILE* fout); /* fct de afisare */
int SrcPrefx(ATrie root, char* key, TCmp idx, Tafi afi, FILE* fout); /* fct de cautare dupa prefix(key) */