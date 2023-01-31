/* ANGHEL Ionela-Carmen - 312CB */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "lista.h"
#include "coada_functii.h"
#include "stiva_functii.h"

#ifndef _NETFLIX_
#define _NETFLIX_

typedef struct serial
{
    int id; /* id serial */
    char *nume; /* nume serial */
    float rating; /* rating serial */
    int nsez; /* numar sezoane serial */
    void *serial; /* coada serial */
    int durt; /* durata totala a serialului */
}SerialQ;

typedef struct sezon
{
    int nep; /* numar de episoade */
    void *eps; /* coada de episoade | un episod e dat de numarul de minute */
}Sez;

/* definitii utile */
#define SCel(a) ((SerialQ*)(a->info)) /* conv info din celula la tip SerialQ */
#define SRL(a) ((SerialQ*)a) /* conv la tip serial */

/* functii de prelucrare a serialelor */
SerialQ* InitSerial(int id, char* nume, float rating, int nsez); /* initializare serial */
SerialQ* CreareSerial(FILE *fin); /* creare serial */
void FreeSerial(void* Asrl); /* eliberare serial */
void AfisareSerial(void* srl); /* afisare serial */
void InsCategorie(SerialQ* srl, TLG* catg, FILE* fout); /* adauga serialul in categorie */
void AfiCateg(void* ct, FILE* fout); /* afisare categorie */
void Add_sez(void* srl, FILE* fin); /* adaugare sezon */
void Add_top(SerialQ* srl, TLG* top); /* adaugare in top10 */

/* functii care prelucreaza stivele si cozile cu info serial */
void* Find_Q(void **c, void *nume, TFCmp cmp); /* cauta fara eliminare in coada */
void* Get_Q(void **c, void *nume, TFCmp cmp); /* cauta cu eliminare in coada */
void* Get_S(void **s, void *nume, TFCmp cmp); /* cauta cu eliminare in stiva */
void* Find_S(void **s, void *nume, TFCmp cmp); /*cauta fara eliminare in stiva */

#endif