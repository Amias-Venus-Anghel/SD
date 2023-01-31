/* ANGHEL Ionela-Carmen - 312CB */

#include "lista.h"

/* inserare la inceput */
int InsLGinc(TLG* aL, void* ae)
{
	TLG aux = malloc(sizeof(TCelulaG));
	if(!aux)
	    return 0;

	aux->info = ae;
	aux->urm = *aL;
	*aL = aux;
	return 1;
}

/* inserare dupa o celula data */
int InsLGdupa(TLG cel, void* ae)
{
    TLG aux = malloc(sizeof(TCelulaG));
	if(!aux)
	    return 0;

	aux->info = ae;
	aux->urm = cel->urm;
    cel->urm = aux;
    return 1;
}

/* inserare la o pozitie data */
int InsLGpoz(TLG* aL, void* ae, int poz)
{
	for(int i = 1; *aL && i < poz; aL = &(*aL)->urm, i++);
	return InsLGinc(aL, ae);
}

/* eliminarea ultimului element*/
void ElimUltim(TLG aL, TFree fr_elem)
{
	TLG ult, pult;
	for(ult = aL; ult->urm; pult = ult, ult = ult->urm);

	pult->urm = NULL;
	fr_elem(ult->info);
	free(ult);
}

/* distrugerea listei */
void DistrLG(TLG* aL, TFree fr_elem) /* distruge lista */
{
	while(*aL != NULL)
    {
        TLG aux = *aL;     /* adresa celulei eliminate */
        if (!aux)
            return;

        fr_elem(aux->info);  /* elib.spatiul ocupat de element*/
        *aL = aux->urm;    /* deconecteaza celula din lista */
        free(aux);   /* elibereaza spatiul ocupat de celula */
    }
}

/* numarul de elemente din lista */
size_t LungimeLG(TLG* aL)
{
	size_t lg = 0;
	TLG p = *aL;

     /* parcurge lista, numarand celulele */
	for (; p != NULL; p = p->urm)
        lg++;

	return lg;
}

/* afisare lista */
void AfiLG(TLG* aL, TAfi afiEL, FILE* fout)
{
	fprintf(fout, " [");
	for(; *aL; aL = &(*aL)->urm)
	{
		afiEL((*aL)->info, fout);
		if((*aL)->urm) /* punem virgula doar daca mai avem elemente de afisat */
			fprintf(fout, ", ");
    }
	fprintf(fout, "].\n");
}


/* verifica daca elementul exista in lista data */
void* Find_elem(TLG aL, void* ae, TFCmp cmp)
{
	for(; aL; aL = aL->urm)
	{
		if(cmp(ae, aL->info))
			return aL->info;
	}
	return NULL;
}

/* extrage elementul cautat si returneaza info sau NULL */
void* Extr_elem(TLG* aL, void* ae, TFCmp cmp)
{
	if(!(*aL)) /* test de lista vida */
		return NULL;

	TLG aux = NULL;
	TLG found = NULL;
	for(; *aL; aL = &(*aL)->urm)
	{
		if(cmp(ae, (*aL)->info))
		{
			found = *aL;
			break; /* daca gasesc elementul se iese din for */
		}
		aux = *aL; /* alfel retin elementul anterior pt refacerea egaturilor */
    }
	if(!aux)
	{
		aux = *aL;
		*aL = (*aL)->urm;
		void* info = aux->info;
		free(aux);
		return info;
	}
	/* s-a parcurs toata lista fara a se gasi elem cauta */
	if(!aux->urm && !found)
		return NULL;

	aux->urm = found->urm;
	void* info = found->info;
	free(found);
	return info;
}