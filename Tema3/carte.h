/* ANGHEL Ionela-Carmen - 312CB */

#define  _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

typedef struct book
{
    char* autor; /* nume autor */
    char* titlu; /* nume carte */
    int rating; /* ratingul cartii */
    int nrpag; /* nr de pagini ale cartii */
}Book, *ABook;

#define MAX 50 /* nr maxim de caractere pentru citire */

/* FUNCTII */
ABook ReadBook(FILE* fin); /* citeste o carte noua */
void FreeBook(void* info); /* fct de eliberare */
void AfiBook(ABook book, FILE* fout); /* fct de afisare */
void AfiBouk(void* info, FILE* fout); /* functie de afisare titlului */
