/* ANGHEL Ionela-Carmen - 312CB */

#include "netflix.h"

#define MAX 50

/* initializare serial */
SerialQ* InitSerial(int id, char* nume, float rating, int nsez)
{
    SerialQ* srl = (SerialQ*)malloc(sizeof(SerialQ));
    if(!srl)
        return NULL; /* alocare esuata */

    srl->serial = InitQ(sizeof(Sez));
    if(!srl->serial)
    {
        free(srl);
        return NULL; /* initializare serial esuata */
    }
    srl->id = id;
    srl->nsez = nsez;
    srl->rating = rating;
    srl->durt = 0;
    srl->nume = nume; /* nume alocat pentru fiecare element */
    return srl;
}

/* creare serial */
SerialQ* CreareSerial(FILE *fin)
{
    int id, nsez;
    float rating;
    char* nume = (char*)malloc(MAX);
    if(!nume)
        return NULL;
    fscanf(fin, "%d%s%f%d", &id, nume, &rating, &nsez);

    SerialQ* srl = InitSerial(id, nume, rating, nsez);
    if(!srl)
    {
        free(nume);
        return NULL;
    }
    int neps; /* numarul de episoade */
    for(int i = 0; i < nsez; i++)
    {
        fscanf(fin, "%d", &neps);
        Sez* sez = (Sez*)malloc(sizeof(Sez));
        if(!sez)
        {
            FreeSerial(srl);
            return NULL;
        }
        if(!InsQ(srl->serial, (void*)sez))
        {
            FreeSerial(srl);
            return NULL;
        }
        sez->nep = neps;
        sez->eps = InitQ(sizeof(int)); /* intializare coada sezon */
        if(!sez->eps)
        {
            FreeSerial(srl);
            return NULL;
        }

        for(int j = 0; j < neps; j++)
        {
            int *min = (int*)malloc(sizeof(int));
            if(!min)
            {
                FreeSerial(srl);
                return NULL;
            }
            fscanf(fin, "%d", min);
            if(!InsQ(sez->eps, (void*)min))
            {
                FreeSerial(srl);
                return NULL;
            }
            srl->durt += *min; /* incrementare durata serial */
        }
    }
    return srl;
}

/* adauga serialul in categorie */
void InsCategorie(SerialQ* srl, TLG* catg, FILE *fout)
{
    if(*catg == NULL) /* categoria este goala */
    {
        if(InsLGinc(catg, srl))
            fprintf(fout, "Serialul %s a fost adaugat la pozitia 1.\n", srl->nume);
        return;
    }
    /* daca elementul trebuie inserat in prima pozitie a listei */
    if( SCel((*catg))->rating < srl->rating)
    {
        if(InsLGinc(catg, srl))
            fprintf(fout, "Serialul %s a fost adaugat la pozitia 1.\n", srl->nume);
        return;
    }
    /* rating egal, nume mai mic */
    if(SCel((*catg))->rating == srl->rating)
        if(strcmp(SCel((*catg))->nume, srl->nume) > 0)
        {
            if(InsLGinc(catg, srl))
                fprintf(fout, "Serialul %s a fost adaugat la pozitia 1.\n", srl->nume);
            return;
        }

    /* daca elementul inserat nu va fi pe prima pozitie */
    TLG p = *catg, aux = p; /* aux retine celula dupa care se insereaza */
    int i = 1; /* retine pozitia pe care se insereaza in lista */
    while(p && SCel(p)->rating >= srl->rating)
    {
        /* verific ordonarea dupa nume */
        if(SCel(p)->rating == srl->rating)
        {

            if(strcmp(SCel(p)->nume, srl->nume) < 0)
            {
                aux = p;
                i++;
            }
        }
        else
        {
            aux = p;
            i++;
        }
        p = p->urm;
    }
    if(InsLGdupa(aux, srl))
        fprintf(fout, "Serialul %s a fost adaugat la pozitia %d.\n", srl->nume, i);
}

/* adauga un sez nou serialului cu nume nume din categoria catg */
void Add_sez(void* srl, FILE* fin)
{
    int neps;
    fscanf(fin, "%d", &neps);
    Sez* sez = (Sez*)malloc(sizeof(Sez));
    if(!sez)
       return;

    if(!InsQ(SRL(srl)->serial, (void*)sez))
    {
        free(sez);
        return;
    }
    sez->nep = neps;
    sez->eps = InitQ(sizeof(int));
    if(!sez->eps)
        return;

    for(int i = 0; i < neps; i++)
    {
        int* min = (int*)malloc(sizeof(int));
        if(!min)
            return;
        fscanf(fin, "%d", min);
        if(!InsQ(sez->eps, (void*)min))
        {
            return;
        }
        SRL(srl)->durt += *min;
    }
    SRL(srl)->nsez++;
}

/* adaugare in top10 */
void Add_top(SerialQ* srl, TLG* top)
{
    InsLGpoz(top, (void*)srl, srl->id);
    /* daca avem un serial care iese din top */
    if(LungimeLG(top) > 10)
        ElimUltim(*top, FreeSerial);
}

/* eliberare memorie serial */
void FreeSerial(void* Asrl)
{
    SerialQ* srl = (SerialQ*)Asrl;
    free(srl->nume);
    void* info = NULL;
    while(!VidaQ(srl->serial))
    {
        ExtrQ(srl->serial, &info);
        Sez* sez = (Sez*)info;
        DistrQ(&sez->eps, free);
        free(sez);
    }
    free(srl->serial);
    free(srl);
}

/* afisare categorie */
void AfiCateg(void* ct, FILE* fout)
{
    fprintf(fout, "(%s, %.1f)", ((SerialQ*)ct)->nume , ((SerialQ*)ct)->rating);
}

/* cauta si returneaza serialul cu numele cerut din coada data, fara sa il elimine */
void* Find_Q(void** c, void* nume, TFCmp cmp)
{
    void* recomp = NULL;
    recomp = InitQ(sizeof(SerialQ));
    if(!recomp)
        return NULL;

    void* elem = NULL;
    void* aux = NULL;
    while(!VidaQ(*c))
    {
        ExtrQ(*c, &elem);
        if(cmp(nume, elem))
            aux = elem;
        InsQ(recomp, elem);
    }
    DistrQ(c, FreeSerial);
    *c = recomp;
    return aux;
}

/* cauta si returneaza serialul cu numele cerut din stiva data, fara sa il elimine */
void* Find_S(void** s, void* nume, TFCmp cmp)
{
    void* recomp = NULL;
    recomp = InitS(sizeof(SerialQ));
    if(!recomp)
        return NULL;
    void* elem = NULL;
    void* aux = NULL;
    while(!VidaS(*s))
    {
        Pop(*s, &elem);
        if(cmp(nume, elem))
            aux = elem;
        Push(recomp, elem);
    }
    Rastoarna(recomp, *s);
    DistrS(&recomp, FreeSerial);
    return aux;
}

/* cauta si returneaza serialul cu numele cerut din coada data, si il elimina din coada */
void* Get_Q(void** c, void* nume, TFCmp cmp)
{
    void* recomp = NULL;
    recomp = InitQ(sizeof(SerialQ));
    if(!recomp)
        return NULL;

    void* elem = NULL;
    void* aux = NULL;
    while(!VidaQ(*c))
    {
        ExtrQ(*c, &elem);
        if(cmp(nume, elem))
            aux = elem;
        else
            InsQ(recomp, elem);
    }
    DistrQ(c, FreeSerial);
    *c = recomp;
    return aux;
}

/* cauta si returneaza serialul cu numele cerut din stiva data, si il elimina din stiva */
void* Get_S(void** s, void* nume, TFCmp cmp)
{
    void* recomp = NULL;
    recomp = InitS(sizeof(SerialQ));
    if(!recomp)
        return NULL;

    void* elem = NULL;
    void* aux = NULL;
    while(!VidaS((*s)))
    {
        Pop(*s, &elem);
        if(cmp(nume, elem))
            aux = elem;
        else
            Push(recomp, elem);
    }
    Rastoarna(recomp, *s);
    DistrS(&recomp, FreeSerial);
    return aux;
}