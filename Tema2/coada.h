/* ANGHEL Ionela-Carmen - 312CB */

#include "coada_functii.h"

#ifndef COADA
#define COADA

typedef struct coada
{
    size_t dime; /* dim element */
    TLG ic, sc; /* adr. prima, ultima celula */
}TCoada, *AQ;

/* definitii utile */
#define IC(a) (((AQ)(a))->ic)
#define SC(a) (((AQ)(a))->sc)
#define DIMEQ(a) (((AQ)(a))->dime)
#define VIDA(a) (((AQ)(a))->ic == NULL && ((AQ)(a))->sc == NULL)

#endif