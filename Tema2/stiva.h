/* ANGHEL Ionela-Carmen - 312CB */

#include "stiva_functii.h"

#ifndef STIVA
#define STIVA

typedef struct stiva
{
    size_t dime; /* dimensiune element */
    TLG vf; /* adresa celului din varf */
}TStiva, *AStiva;

/* definitii utile */
#define VF(a) (((AStiva)(a))->vf)
#define DIME(a) (((AStiva)(a))->dime)
#define VIDA_S(a) (((AStiva)(a))->vf == NULL)

#endif