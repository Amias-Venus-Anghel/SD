/* ANGHEL Ionela-Carmen - 312CB */

#include "stiva.h"

/* initializare stiva */
void* InitS(size_t d)
{
    AStiva s;
    s = (AStiva)malloc(sizeof(TStiva));
    if(!s)
        return NULL;

    s->dime = d;
    s->vf = NULL;

    return (void*)s;
}

/* adaugare element in varful stivei */
int Push(void* s, void* elem)
{
    /* returneaza 0 pentru inserare esuata
       si 1 pentru inserare reusita */

    TLG aux;
    aux = (TLG)malloc(sizeof(TCelulaG));
    if(!aux)
        return 0; /* eroare de alocare */
    aux->info = elem; /* elem este alocat pentru fiecare element inserat */
    aux->urm = VF(s);
    VF(s) = aux;
    return 1;
}

/* extragere din stiva */
int Pop(void* s, void** elem)
{
    TLG aux = VF(s); /* varful stivei */
    if(!aux)
        return 0; /* extragere esuata, nu avem elemente */

    *elem = aux->info; /* elem se muta la adresa elementului */
    VF(s) = aux->urm;
    free(aux);
    return 1; /* extragere reusita */
}

/* resetare stiva */
void ResetS(void* s, TFree f)
{
    TLG aux = VF(s);
    while (aux)
    {
        TLG p = aux;
        aux = aux->urm;
        f(p->info); /* eliberare p info */
        free(p);
    }
    VF(s) = NULL;
}

/* distrugere stiva */
void DistrS(void** s, TFree f)
{
    ResetS(*s, f);
    free(*s);
    (*s) = NULL;
}

/* rastoarna stiva s in stiva d */
int Rastoarna(void* s, void* d)
{
    /* returneaza 1/0 pentru operatie reusita/esuata */
    if(DIME(s) != DIME(d))
        return 0;
    if(!VF(s))
        return 0;
    TLG p = VF(s); /* pointer pentru parcurgere */
    TLG aux;
    while(p)
    {
        aux = p->urm;
        p->urm = VF(d);
        VF(d) = p;
        p = aux;
    }
    VF(s) = NULL;
    return 1;
}

/* afisare stiva */
void AfiS(void* s, TAfi afiEl, FILE* fout)
{
    TLG aL = VF(s);
    AfiLG(&aL, afiEl, fout);
}

/* stiva vida */
int VidaS(void* s)
{
    return VIDA_S(s);
}