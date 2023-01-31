/* ANGHEL Ionela Carmen - 312CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


typedef int (*TFHash)(void*, int, int); /* functie de obtinere a hashului */
typedef int (*TFCmp)(void*, void*, int); /* functie de comparare doua elemente */
typedef void (*Tafi)(void*, FILE*);     /* functie afisare un element */
typedef void (*Tfre)(void*); /* fct eliberare */

typedef struct celula2
{
  void *info;              /* adresa element extern */
  struct celula2 *pre, *urm;  /* legaturi spre celulele vecine */
} TCelula2, *TLDI;

typedef struct
{
  size_t M;
  TFHash hash;
  TLDI *v; /* vector de liste */
} THash;

typedef struct
{
  char *key; /*linkul site-ului*/
  char *value; /*adresa ip a site-ului*/
}adresaIP;

THash* InitTHash(size_t M, TFHash fctHash); /*fct de initializare a tabelei hash*/
int Put(THash *h, void *el, TFCmp cmp); /*fct de adaugare a unui element in tabela*/
void PrintH(THash *h, Tafi afiEL, FILE *fout); /*functie de afisare a tabelei*/
void* Get(THash *h, char *key, TFCmp cmp); /*functie de obtinere a adresei informatiei cautate*/
int Find(THash *h, char *key, TFCmp cmp, FILE *fout); /*functie de verificare a existentei informatiei*/
void PrintBucket(THash *h, int cod, Tafi afiEl, FILE *fout); /*functie de afisare a listei cerute*/
void Remove(THash *h, char *key, TFCmp cmp, Tfre freInfo); /*functie de stergere a unui element*/
void DistrTH(THash** h, Tfre freEl); /*functie de eliberare a memoriei*/