/* ANGHEL Ionela Carmen - 312CB */
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
    int cod = h->hash(el, h->M, 1);

    TLDI p, aux = NULL; /* aux retine elementul dupa care el va fi inserat */
    p = h->v[cod]; 
    do
    {
        if(!p) /* daca lista e vida iesim din parcurgere */
            break;
        if(!cmp(p->info, el, 0)) /* elementu exista deja */
        {
            return 0;
        }
        else if(cmp(p->info, el, 0) < 0) /* pentru ordonarea corecta in lista */
        {
            aux = p;
        }
        p = p->urm;

    } while ( p && p != h->v[cod]); /* parcurgem pana cand ajungem iar la primul element */
    

    TLDI new = malloc(sizeof(TCelula2));
    new->info = el;
    if(!new)
    {
        printf("eroare alocare celula noua la inserare\n");
        return 0;
    }
   
    if(!aux) /* el e primul element din lista */
    {

        if(!p) /* primu element din lista ever */
        {
            h->v[cod] = new;
            new->urm = new;
            new->pre = new;
            return 1;
        }
        else /* tre adaugata la inceputul listei */
        {
            new->pre = h->v[cod]->pre;
            new->urm = h->v[cod];
            new->urm->pre = new;
            new->pre->urm = new;
            h->v[cod] = new; 
            return 1;
        }

    }

    /* nu e primul el din lista si s-a gasit un aux dupa care va fi inserat*/
    new->urm = aux->urm;
    aux->urm->pre = new;
    aux->urm = new;
    new->pre = aux;

    return 1;
}

void PrintH(THash *h, Tafi afiEl, FILE *fout)
{
    TLDI p, el;
    int i;
    for(i = 0; i < h->M; i++) 
    {
        p = h->v[i];
        if(p) 
        {
            el = p;
            fprintf(fout, "%d: ",i);
            do
            {
                afiEl(el->info, fout);
                el = el->urm;
            } while (el != p);
            fprintf(fout, "\n");
        }
    }
}

void PrintBucket(THash *h, int cod, Tafi afiEl, FILE *fout)
{
    if(cod >= h->M)
    {
        /* codul nu se afla in lista posibila de coduri ale tabelei hash */
        return;
    }
    if(!h->v[cod])
    {
        fprintf(fout, "VIDA\n");
        return;
    }

    TLDI el;

    el = h->v[cod];
    do
    {
        afiEl(el->info, fout);
        el = el->urm;
    } while (el != h->v[cod]);
    fprintf(fout, "\n");   
}

void* Get(THash *h, char *key, TFCmp cmp)
{
    int cod = h->hash(key, h->M, 0);
    TLDI p = h->v[cod];
  
    do
    {
        if(!p) /* lista vida */
            return NULL;
        if(!cmp(p->info, key, 1)) /* elementu exista */
        {
            return p->info; 
        }
        p = p->urm;

    } while ( p && p != h->v[cod]); /* parcurgem pana cand ajungem iar la primul element */
    
    /* nu s-a gasit */
    return NULL; 
}

int Find(THash *h, char *key, TFCmp cmp, FILE *fout) 
{
    int cod = h->hash(key, h->M, 0);
    TLDI p = h->v[cod];
  
    do
    {
        if(!p) 
        {
            /* lista vida */
            fprintf(fout, "False\n");
            return 0;
        }
        if(!cmp(p->info, key, 1)) 
        {
            fprintf(fout, "True\n");
            return 1;
        }
        p = p->urm;

    } while ( p && p != h->v[cod]); 

    /* nu s-a gasit */
    fprintf(fout, "False\n");
    return 0;
}

void Remove(THash *h, char *key, TFCmp cmp, Tfre freInfo)
{
    int cod = h->hash(key, h->M, 0);
    TLDI p = h->v[cod];
  
    do
    {
        if(!p) 
            return;
        if(!cmp(p->info, key, 1)) 
        {
            if(p->urm == p)
            {
                /* e singurul element -> lista devine nula */
                freInfo(p->info);
                free(p);
                h->v[cod] = NULL;
                return;
            }
            if(p == h->v[cod]) /* se schimba capul listei */
                h->v[cod] = p->urm;
            
            /*restul se intampla la eliminarea oricarui alt element*/
            p->urm->pre = p->pre;
            p->pre->urm = p->urm;
            freInfo(p->info);
            free(p);
            return;
            
        }
        p = p->urm;

    } while ( p && p != h->v[cod]); 

    /* nu s-a gasit */
}

void DistrTH(THash** h, Tfre freEl)
{
    TLDI *p, el, aux;

    /* parcurgere cu pointeri */
    for (p = (*h)->v; p < (*h)->v + (*h)->M; p++) 
    {
        /* daca exista elemente corespunzatoare acestui hash
        eliberam info din celula si apoi eliberam celula */
        el = *p;
        do
        {
            if(!el) 
                break;
            aux = el;
            el = el->urm;
            freEl(aux->info);
            free(aux);

        } while (el != *p); 

    }
    free((*h)->v);
    free(*h);
    *h = NULL;
}