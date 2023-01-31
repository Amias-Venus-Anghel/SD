/* ANGHEL Ionela-Carmen - 312CB */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_

typedef struct celulag
{
  void* info;           /* adresa informatie */
  struct celulag *urm;   /* adresa urmatoarei celule */
} TCelulaG, *TLG; /* tipurile Celula, Lista  */

typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TFree)(void*);     /* functie eliberare un element */
typedef void (*TAfi)(void*, FILE*); /* functie afisare un element */

/* functii lista generica */
int InsLGinc(TLG*, void*);  /*- inserare la inceput reusita sau nu (1/0) */
int InsLGdupa(TLG, void*); /* ins la final */
void DistrLG(TLG* aL, TFree fe); /* distruge lista */
size_t LungimeLG(TLG*);   /* numarul de elemente din lista */
void AfiLG(TLG*, TAfi, FILE*); /* afisare lista */
void* Find_elem(TLG aL, void* elem, TFCmp cmp); /* verfica daca elementul exista in lista data */
void ElimUltim(TLG aL, TFree fr_elem); /* elimina ultimul element */
int InsLGpoz(TLG *aL, void *ae, int poz); /* inserare pe pozitia poz */
void* Extr_elem(TLG* aL, void* elem, TFCmp cmp); /* extrage elementul cautat din lista */

#endif
