#include "tema1.h"


THash* InitTHash(size_t M, TFHash fctHash)
{
    THash* h = (THash *) calloc(sizeof(THash), 1);
    if (!h) 
    {
        printf("eroare alocare hash\n");
        return NULL;
    }

    h->v = (TLDI*) calloc(M, sizeof(TLDI));
    if(!h->v) 
    {
        printf("eroare alocare vector de pointeri TLDI in hash\n");
        free(h);
        return NULL;
    }

    h->M = M;
    h->hash = fctHash;
    return h;
}

int Put(THash *h, void *el, TFCmp cmp)
{
    int cod = h->hash(((adresaIP*)el)->key, h->M);
    //printf("DEBUG: key: %s cod hash: %d\n", ((adresaIP*)el)->key, cod );
    TLDI p, aux = NULL; //aux retine ultimul element care se afla dupa el daca el va fi inserat (cmp>0) pt inserare directa
    p = h->v[cod]; // verificare separata pentru primul element, pentru a putea identifica ciclul complet al forului.
    //printf("DEBUG: adresa p/h.v[cod]: %p\n", p);
    if(p && p == p->urm) // p exista si e singurul element
    {   
        if(!cmp(p->info, ((adresaIP*)el)->key)) // elementu de inserat exista
        {
            return 0;
        }
        else if(cmp(p->info, ((adresaIP*)el)->key) < 0) //elementul de inserat trebuie inserat dupa/inainte
        {
            aux = p;
        }
        p = h->v[cod]->urm; // grija mare aici, trece la urm element doar daca exista p. daca p e null, nu va intra in for oricum
    }

    for(; p != NULL && p != h->v[cod]; p = p->urm) // merge cat timp p nu e null (lista vida) si p nu a facut un tur complet prin toate valoriile listei
    {
        if(!cmp(p->info, ((adresaIP*)el)->key))
        {
            return 0;
        }
        else if(cmp(p->info, ((adresaIP*)el)->key) < 0)
        {
            aux = p;
        }
    }

    TLDI new = malloc(sizeof(TCelula2));
    new->info = el;
    if(!new)
    {
        printf("eroare alocare celula noua la inserare\n");
        return 0;
    }
   
    if(!aux) // caz in care e primul element din lista asta  sau daca trebuie inserat in fata tuturor elementelor din lista
    {

        if(!p) // primu element din lista ever
        {
            h->v[cod] = new;
            new->urm = new;
            new->pre = new;
            return 1;
        }
        else //tre adaugata la inceput
        {
            new->pre = h->v[cod]->pre;
            new->urm = h->v[cod];
            h->v[cod] = new;
            return 1;
        }

    }

    //daca nu e primul el din lista, dar tre inserat, si s-a gasit un aux dupa care va fi inserat
    new->urm = aux->urm;
    aux->urm->pre = new;
    aux->urm = new;
    new->pre = aux;

    return 1;
}

void PrintH(THash *h, Tafi afiEl, FILE *fout)
{
    TLDI p, el;
    for(int i = 0; i < h->M; i++) 
    {
        p = h->v[i];
        if(p) 
        {
            fprintf(fout, "%d: ",i);
            afiEl(p->info, fout);
            for(el = p->urm; el != p; el = el->urm)
                afiEl(el->info, fout);
            fprintf(fout, "\n");
        }
    }
}

void PrintBucket(THash *h, int cod, Tafi afiEl, FILE *fout)
{
    if(!h->v[cod])
    {
       fprintf(fout, "VIDA\n");
        return;
    }

    TLDI el;

    //fprintf(fout, "%d: ",cod); fara cod inainte de elemente
    afiEl(h->v[cod]->info, fout);
    for(el = h->v[cod]->urm; el != h->v[cod]; el = el->urm)
        afiEl(el->info, fout);
    fprintf(fout, "\n");
    
}

char* Get(THash *h, char *key, TFCmp cmp)
{
    int cod = h->hash(key, h->M);
    TLDI p = h->v[cod];
    if(!p)
    {
        //nu exista elemente la acest hash, deci nici elemtul cautat
        return NULL;
    }

    if(!cmp(p->info, key))
    {
        return ((adresaIP*)(p->info))->value;
    }

    for(p = p->urm; p != h->v[cod]; p = p->urm)
    {
        if(!cmp(p->info, key))
        {
            return ((adresaIP*)(p->info))->value;
        }
    }

    return "NULL"; // nu s-a gasit
}

int Find(THash *h, char *key, TFCmp cmp, FILE *fout) //intoarce 0/1 
{
    int cod = h->hash(key, h->M);
    TLDI p = h->v[cod];
    if(!p)
    {
        //nu exista elemente la acest hash, deci nici elemtul cautat
        fprintf(fout, "False\n");
        return 0;
    }

    if(!cmp(p->info, key))
    {
        fprintf(fout, "True\n");
        return 1;
    }

    for(p = p->urm; p != h->v[cod]; p = p->urm)
    {
        if(!cmp(p->info, key))
        {
            fprintf(fout, "True\n");
            return 1;
        }
    }

    fprintf(fout, "False\n");
    return 0;
}

void Remove(THash *h, char *key, TFCmp cmp, Tfre freInfo)
{
    int cod = h->hash(key, h->M);
    TLDI p = h->v[cod];
    if(!p)
        return;
    if(!cmp(p->info, key)) // e primul element din lista
    {
        if(p->urm == p)
        {
            //e singurul element din lista, deci lista devine nula
            freInfo(p->info);
            free(p);
            h->v[cod] = NULL;
            return;
        }

        h->v[cod] = p->urm;
        p->urm->pre = p->pre;
        p->pre->urm = p->urm;
        freInfo(p->info);
        free(p);
        return;
    }

    //cautam in lista elemntul
    for(p = p->urm; p != h->v[cod]; p = p->urm)
    {
        if(!cmp(p->info, key))
        {
            p->urm->pre = p->pre;
            p->pre->urm = p->urm;
            freInfo(p->info);
            free(p);
            return;
        }
    }

    //nu s-a gasit

}