/* ANGHEL Ionela-Carmen - 312CB */

#include "coada.h"

/* initializare coada */
void* InitQ(size_t d)
{
    AQ c;
    c = (AQ)malloc(sizeof(TCoada));
    if(!c)
        return NULL;

    c->dime = d;
    c->ic = NULL;
    c->sc = NULL;

    return (void*)c;
}

/* inserare elem in coada */
int InsQ(void* c, void* elem)
{
    TLG aux = (TLG)malloc(sizeof(TCelulaG));
    if(!aux)
        return 0; /* inserare esuata */
    aux->info = elem; /* elem e alocat per fiecare inserare */
    aux->urm = NULL;
    if(VIDA(c)) /* inserare in coada vida */
    {
        IC(c) = aux;
        SC(c) = aux;
        return 1;
    }
    else /* inserare in coada nevida */
    {
        SC(c)->urm = aux;
        SC(c) = aux;
        return 1;
    }
}

/* extragere din coada */
int ExtrQ(void* c, void** elem)
{
    if(VIDA(c))
        return 0; /* extragere esuata, nu avem ce extrage */

    TLG aux;
    if(IC(c) != SC(c)) /* coada cu mai multe elemente */
    {
        aux = IC(c);
        IC(c) = aux->urm;
    }
    else /* coada cu un singur element */
    {
        aux = IC(c);
        IC(c) = NULL; /* devine coada vida */
        SC(c) = NULL;
    }
    *elem = aux->info;
    free(aux);
    return 1;
}

/* resetare coada */
void ResetQ(void* c, TFree f)
{
    TLG aux = IC(c);
    while (aux)
    {
        TLG p = aux;
        aux = aux->urm;
        f(p->info); /* eliberare p info */
        free(p);
    }
    IC(c) = NULL;
    SC(c) = NULL;
}

/* distrugere coada */
void DistrQ(void** c, TFree f)
{
    ResetQ(*c, f);
    free(*c);
    (*c) = NULL;
}

/* lungimea cozii */
int LgQ(void* c)
{
    size_t lg = 0;
	TLG p = IC(c);

     /* parcurge lista, numarand celulele */
	for (; p != NULL; p = p->urm)
        lg++;

	return lg;
}

/* afisare coada */
void AfiQ(void* c, TAfi afiEl, FILE* fout)
{
    TLG aL = IC(c);
    AfiLG(&aL, afiEl, fout);
}

/* coada vida */
int VidaQ(void* c)
{
    return VIDA(c);
}