/* ANGHEL Ionela-Carmen - 312CB */

#include "netflix.h"

#define MAX 50 /*valuare maxima pentru alocarea sirurilor de citire*/

/* functie de comparare */
int CmpSrl(void* elem, void* info)
{
    char* nume = ((SerialQ*)info)->nume;
    if(!strcmp(elem, nume))
        return 1;
    return 0;
}

int main(int argc, char* argv[])
{
    char* f_in = argv[1];
    char* f_out = argv[2];
    char* comanda = (char*)malloc(MAX);
    if(!comanda)
        return 1; /* eroare de alocare */

    FILE* fin = fopen(f_in, "r");
    FILE* fout = fopen(f_out, "w");

    TLG catg1 = NULL, catg2 = NULL, catg3 = NULL, top10 = NULL; /*id corespz: 1, 2, 3, poz inserare in top*/
    void* later = InitQ(sizeof(SerialQ));
    if(!later)
        return 1;

    void* watching = InitS(sizeof(SerialQ));
    if(!watching)
    {
        free(later);
        return 1;
    }
    void* history = InitS(sizeof(SerialQ));
    if(!history)
    {
        free(later);
        free(watching);
        return 1;
    }

    while(fscanf(fin, "%s", comanda) != EOF)
    {
        if(!strcmp(comanda, "add"))
        {
            SerialQ* srl = CreareSerial(fin);
            if(!srl)
                return 1;
            switch (srl->id)
            {
            case 1:
                InsCategorie(srl, &catg1, fout);
                break;
            case 2:
                InsCategorie(srl, &catg2, fout);
                break;
            case 3:
                InsCategorie(srl, &catg3, fout);
                break;
            }
        }
        else if (!strcmp(comanda, "show"))
        {
            char* categ = (char*)malloc(MAX);
            if(!categ)
                return 1;
            fscanf(fin, "%s", categ);
            fprintf(fout, "Categoria %s:", categ);
            /* afisare categorie */
            if(!strcmp(categ, "1"))
                AfiLG(&catg1, AfiCateg, fout);
            else if(!strcmp(categ, "2"))
                AfiLG(&catg2, AfiCateg, fout);
            else if(!strcmp(categ, "3"))
                AfiLG(&catg3, AfiCateg, fout);
            else if(!strcmp(categ, "top10"))
                AfiLG(&top10, AfiCateg, fout);
            else if(!strcmp(categ, "later"))
                AfiQ(later, AfiCateg, fout);
            else if(!strcmp(categ, "watching"))
                AfiS(watching, AfiCateg, fout);
            else if(!strcmp(categ, "history"))
                AfiS(history, AfiCateg, fout);
            free(categ);
        }
        else if(!strcmp(comanda, "add_sez"))
        {
            char* nume =(char*)malloc(MAX);
            if(!nume)
                return 1;
            fscanf(fin, "%s", nume);
            void* srl = NULL;
            /* cautare serial */
            srl = Find_elem(catg1, (void*)nume, CmpSrl);
            if(!srl)
                srl = Find_elem(catg2, (void*)nume, CmpSrl);
            if(!srl)
                srl = Find_elem(catg3, (void*)nume, CmpSrl);
            if(!srl)
                srl = Find_elem(top10, (void*)nume, CmpSrl);
            if(!srl)
                srl = Find_Q(&later, (void*)nume, CmpSrl);
            if(!srl)
                srl = Find_S(&watching, (void*)nume, CmpSrl);

            if(srl)
            {
                Add_sez(srl, fin);
                fprintf(fout, "Serialul %s are un sezon nou.\n", nume);
            }
            free(nume);
        }
        else if(!strcmp(comanda, "add_top"))
        {
            SerialQ* srl = CreareSerial(fin);
            if(!srl)
                return 1;
            Add_top(srl, &top10);
            fprintf(fout, "Categoria top10:");
            AfiLG(&top10, AfiCateg, fout);
        }
        else if(!strcmp(comanda, "later"))
        {
            char* nume =(char*)malloc(MAX);
            if(!nume)
                return 1;
            fscanf(fin, "%s", nume);

            /* caut categoria in care se afla serialul si il extrag */
            void *srl = NULL;

            srl = Extr_elem(&catg1, (void*)nume, CmpSrl);
            if(!srl)
                srl = Extr_elem(&catg2, (void*)nume, CmpSrl);
            if(!srl)
                srl = Extr_elem(&catg3, (void*)nume, CmpSrl);
            if(!srl)
                srl = Extr_elem(&top10, (void*)nume, CmpSrl);

            if(srl)
            {
                InsQ(later, srl);
                fprintf(fout, "Serialul %s se afla in coada de", nume);
                fprintf(fout, " asteptare pe pozitia %d.\n", LgQ(later));
            }

            free(nume);
        }
        else if(!strcmp(comanda, "watch"))
        {
            char* nume =(char*)malloc(MAX);
            if(!nume)
                return 1;
            fscanf(fin, "%s", nume);

            int dur;   /* durata de vizionare */
            fscanf(fin, "%d", &dur);

            /* caut categoria in care se afla serialul */
            void *srl = NULL;
            srl = Extr_elem(&catg1, (void*)nume, CmpSrl);
            if(!srl)
                srl = Extr_elem(&catg2, (void*)nume, CmpSrl);
            if(!srl)
                srl = Extr_elem(&catg3, (void*)nume, CmpSrl);
            if(!srl)
                srl = Extr_elem(&top10, (void*)nume, CmpSrl);
            /* daca serialul nu e in una din cele 4 categorii se cauta in coada later */
            if(!srl)
                srl = Get_Q(&later, nume, CmpSrl);
            /* daca serialul nu e gasit, se cauta in stiva watching */
            if(!srl)
                srl = Get_S(&watching, nume, CmpSrl);

            if(srl)
            {
                Push(watching, srl);
                ((SerialQ*)srl)->durt -= dur;
                if(((SerialQ*)srl)->durt <= 0)
                {
                    fprintf(fout, "Serialul %s a fost vizionat integral.\n", nume);
                    Pop(watching, srl);
                    Push(history, srl);
                }
            }

            free(nume);
        }
    }
    free(comanda);

    /* eliberari de memorie */
    DistrLG(&catg1, FreeSerial);
    DistrLG(&catg2, FreeSerial);
    DistrLG(&catg3, FreeSerial);
    DistrLG(&top10, FreeSerial);
    DistrQ(&later, FreeSerial);
    DistrS(&watching, FreeSerial);
    DistrS(&history, FreeSerial);
    free(later);

    fclose(fin);
    fclose(fout);

    return 0;
}