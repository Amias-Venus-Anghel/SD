/* ANGHEL Ionela Carmen - 312CB */
#include <stdio.h>
#include "tema1.h"

#define MAX 100 /*valuare maxima pentru alocarea sirurilor de citire*/

int codHash(void *el, int M, int tip)
{   
    /*tip e 1 daca primim element din tabela sau 0 daca primim un sir de caractere*/
    char* sir;
    if(tip)
        sir = ((adresaIP*)el)->key;
    else
        sir = el;

    int n = strlen(sir); /* nr de elemente */ 
    int cod = 0;
   
    int i;
    for(i = 0; i < n; i++)
    {
        cod += (int)(sir[i]); //incrementare cod       
    }

    return cod % M;    
}

int compKey(void *adresa, void *key, int tip) 
{
    /*tip e 1 daca primim un element de tip adresa si un sir, 0 daca primim 2 elemente de tip adresa */
    if(tip)
        return strcmp( ((adresaIP*)adresa)->key, (char*)key);
    else
        return strcmp( ((adresaIP*)adresa)->key, ((adresaIP*)key)->key);   
}

void* AlocareEl(char *key, char *value)
{
    adresaIP *elNew = (adresaIP*)malloc(sizeof(adresaIP));
    if(!elNew)
    {
        printf("eroare alocare memorie Put\n");
        return 0;
    }
     
    elNew->key = malloc(MAX);
    elNew->value = malloc(MAX);
    strcpy(elNew->key, key);
    strcpy(elNew->value, value);

    return (void*)elNew;
}

void AfiEl(void *el, FILE *fout)
{
    fprintf(fout, "%s ", ((adresaIP*)el)->value);
}

void FrAdresa(void *info)
{
    free( ((adresaIP*)info)->key);
    free( ((adresaIP*)info)->value);
    free(info);
}

int main(int argc, char *argv[])
{
    char *fin = argv[2];
    char *fout = argv[3];
    char *comanda = (char*)malloc(MAX);

    FILE *f_in = fopen(fin, "r");
    FILE *f_out = fopen(fout, "w");
    int M = atoi(argv[1]);

    THash *tabela = (THash*)InitTHash(M, codHash);
    
    while (fscanf(f_in ,"%s", comanda) != EOF)
    {

        char *link = (char*)malloc(MAX);
        char *adresa = (char*)malloc(MAX);
        if (!strcmp(comanda, "put"))
        {
            fscanf(f_in, "%s%s", link, adresa);
            void *ins = AlocareEl(link, adresa);
            int inserat = Put(tabela, ins, compKey); 

            /* daca nu a fost inserat, eliberez memoria alocata elementului*/
            if(!inserat) 
                FrAdresa(ins);
        }
        else if(!strcmp(comanda, "get"))
        {
            fscanf(f_in, "%s", link);
            void *rez = Get(tabela, link, compKey);
            if(rez)
                fprintf(f_out, "%s\n", ((adresaIP*)rez)->value);
            else 
                fprintf(f_out, "NULL\n");
        }
        else if(!strcmp(comanda, "remove"))
        {
            fscanf(f_in, "%s", link);
            Remove(tabela, link, compKey, FrAdresa);
        }
        else if(!strcmp(comanda, "find"))
        {
            fscanf(f_in, "%s", link);
            Find(tabela, link, compKey, f_out);
        }
        else if(!strcmp(comanda, "print"))
        {
            PrintH(tabela, AfiEl, f_out);
        }
        else if(!strcmp(comanda, "print_bucket"))
        {
            int cod;
            fscanf(f_in, "%d", &cod);
            PrintBucket(tabela, cod, AfiEl, f_out);
        }
        free(link);
        free(adresa);
    }

    free(comanda);
    fclose(f_in);
    fclose(f_out);
    DistrTH(&tabela, FrAdresa);
    return 0;
}