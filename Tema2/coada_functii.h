/* ANGHEL Ionela-Carmen - 312CB */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "lista.h"

#ifndef COADA_F
#define COADA_F

/* functii coada */
void* InitQ(size_t d); /* initializare coada */
int InsQ(void *c, void *elem); /* inserare elem in coada */
int ExtrQ(void *c, void **elem); /* extragere din coada */
void ResetQ(void *c, TFree f); /* resetare coada */
void DistrQ(void **c, TFree f); /* distrugere coada */
int LgQ(void* c); /* lungimea cozii */
void AfiQ(void *c, TAfi afiEl, FILE* fout); /* afisare coada */
int VidaQ(void *c); /* coada vida */

#endif