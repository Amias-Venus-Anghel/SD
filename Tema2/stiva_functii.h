/* ANGHEL Ionela-Carmen - 312CB */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "lista.h"

#ifndef STIVA_F
#define STIVA_F

/* functii cu stive */
void* InitS(size_t d); /* initializare stiva */
int Push(void *s, void *elem); /* adaugare element in varful stivei */
int Pop(void *s, void **elem); /* extragere din stiva */
void ResetS(void *s, TFree f); /* resetare stiva */
void DistrS(void **s, TFree f); /* distrugere stiva */
int Rastoarna(void *s, void *d); /* rastoarna stiva s in stiva d */
void AfiS(void *s, TAfi afiEl, FILE* fout); /* afisare */
int VidaS(void* s); /* stiva vida */

#endif