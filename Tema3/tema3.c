/* ANGHEL Ionela-Carmen - 312CB */
#define  _GNU_SOURCE
#include "trie.h"
#include "carte.h"

/* functie de calculare a indexului */
int CharToIndex(char c)
{
    /* contruiesc alfabetul */
    char alf[68] = "abcdefghijklmnopqrstuvwxyz";
    char b[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char bb[] = "0123456789.-'?! ";
    strcat(alf, b);
    strcat(alf, bb);

    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
        if( alf[i] == c)
            return i;
    }

    return -1; /* nu se ajunge aici*/
}

/* functie pentru eliberarea lui T2 */
void FreeT2info(void* info)
{
    ATrie Tautor = (ATrie)info;
    free_all(Tautor); /* eliberam structura fara info */
}

/* functie de afisare a autorului */
void AfiAutor(void* info, FILE* fout)
{
    /* parcurg arborele pentru a ajunge la o structura de unde pot citi numele autorului */
    /* trie parcurgere in adancime */
    ATrie autor = (ATrie)info;
    while(!autor->isEndOfWord)
    {
        for(int i = 0; i < ALPHABET_SIZE; i++)
        {
            if(autor->children[i])
            {
                autor = autor->children[i];
                break; /* daca am gasit un copil trecem mai departe */
            }
        }
    }
    fprintf(fout, "%s\n", ((ABook)autor->info)->autor);
}

/* adaugare carte in recomandari */
void add_book(FILE* fin, ATrie T1, ATrie T2)
{
    /* citesc cartea */
    ABook book = ReadBook(fin);
    /* verific daca castea exista deja in Trie */
    void *check = Get(T1, book->titlu, CharToIndex);
    if(!check)
    {
        /* inserare in T1 */
        Insert(T1, book->titlu, CharToIndex, (void*)book);

        /* verific daca exista deja autorul in T2 */
        ATrie Tautor = (ATrie)Get(T2, book->autor, CharToIndex);
        if(!Tautor) /* autor nu exista deja */
        {
            Tautor = GetNode();
            Insert(T2, book->autor, CharToIndex, (void*)Tautor);
        }
        Insert(Tautor, book->titlu, CharToIndex, (void*)book);
    }
    else
        FreeBook(book);
}

/* cautare carte in recomandari */
void search_book(FILE* fin, FILE* fout, ATrie T1)
{
    char* citit = NULL;
    size_t len = 0;
    getline(&citit, &len, fin);

    /* verific daca se cere autocomplete */
    char* p = strchr(citit, '~');

    if(!p) /* p = NULL deci nu avem autocomplete */
    {
        char* titlu = strtok(citit+1, "\n");
        // titlu[strlen(titlu)-1]='\0'; /* linia magica */
        ABook book = (ABook)Get(T1, titlu, CharToIndex);
        if(!book)
        {
            fprintf(fout, "Cartea %s", titlu);
            fprintf(fout, " nu exista in recomandarile tale.\n");
        }
        else
            AfiBook(book, fout);
    }
    else
    {
        /* autocomplete */
        char* semi_tl = strtok(citit+1, "~"); // nu mai e linia magica
        int n = SrcPrefx(T1, semi_tl, CharToIndex, AfiBouk, fout);
        if(!n)
            fprintf(fout, "Nicio carte gasita.\n");
    }
    free(citit);
}

/* cautare autor in recomandari */
void list_author(FILE* fin, FILE* fout, ATrie T2)
{
    char* citit = NULL;
    size_t len = 0;
    getline(&citit, &len, fin);

    /* verific daca se cere autocomplete */
    char* p = strchr(citit, '~');

    if(!p) /* p = NULL deci nu avem autocomplete */
    {
        char* autor = strtok(citit+1, "\n");
        // autor[strlen(autor)-1]='\0'; /* linia magica */
        ATrie Tautor = (ATrie)Get(T2, autor, CharToIndex);
        if(Tautor)
            AfiTrie(Tautor, AfiBouk, fout);
        else
        {
            fprintf(fout,"Autorul %s ", autor);
            fprintf(fout,"nu face parte din recomandarile tale.\n");
        }
    }
    else
    {
        /* autocomplete */
        char* semi_aut = strtok(citit+1, "~"); // nu mai e linia magica
        int n = SrcPrefx(T2, semi_aut, CharToIndex, AfiAutor, fout);
        if(!n)
            fprintf(fout, "Niciun autor gasit.\n");
    }
    free(citit);
}

/* cautare dupa autor */
void search_by_author(FILE* fin, FILE* fout, ATrie T2)
{
    char* citit = NULL;
    size_t len = 0;
    getline(&citit, &len, fin);

    /* verific daca se cere autocomplete */
    char* p = strchr(citit, '~');

    if(!p) /* fara autocomplete */
    {
        char* autor = strtok(citit+1, ":");
        char* titlu = strtok(NULL, "\n");
        // autor[strlen(autor)-1] = '\0'; /* linia magica */
        ATrie Tautor = (ATrie)Get(T2, autor, CharToIndex);
        if(!Tautor)
        {
            fprintf(fout,"Autorul %s ", autor);
            fprintf(fout,"nu face parte din recomandarile tale.\n");
        }
        else
        {
            ABook book = (ABook)Get(Tautor, titlu, CharToIndex);
            if(!book)
            {
                fprintf(fout, "Cartea %s", titlu);
                fprintf(fout, " nu exista in recomandarile tale.\n");
            }
            else
                AfiBook(book, fout);
        }
    }
    else
    {
        /* verific daca se cere autocompletare la titlu */
        char* p2 = strchr(citit, ':');

        if(!p2)
        {
            /* autocomplete la autor */
            char* semi_aut = strtok(citit+1, "~"); // nu mai e linia magica
            int n = SrcPrefx(T2, semi_aut, CharToIndex, AfiAutor, fout);
            if(!n)
                fprintf(fout, "Niciun autor gasit.\n");
        }
        else
        {
            char* autor = strtok(citit+1, ":");
            char* semi_tl = strtok(NULL, "~"); // fara linia magica la autor

            /* caut autorul in T2 */
            ATrie Tautor = (ATrie)Get(T2, autor, CharToIndex);
            if(!Tautor)
            {
                fprintf(fout,"Autorul %s ", autor);
                fprintf(fout,"nu face parte din recomandarile tale.\n");
            }
            else
            {
                int n = SrcPrefx(Tautor, semi_tl, CharToIndex, AfiBouk, fout);
                if(!n)
                    fprintf(fout, "Nicio carte gasita.\n");
            }
        }
    }

    free(citit);
}

int main(int argc, char* argv[])
{
    char* f_in = argv[1];
    char* f_out = argv[2];
    char* comanda = (char*)malloc(MAX);
    if(!comanda)
        return 1;

    FILE* fin = fopen(f_in, "r");
    FILE* fout = fopen(f_out, "w");

    ATrie T1 = GetNode();
    ATrie T2 = GetNode();

    /* identificare comanda */
    while(fscanf(fin, "%s", comanda) != EOF)
    {
        if(!strcmp("add_book", comanda))
        {
            add_book(fin, T1, T2);
        }
        else if(!strcmp("search_book", comanda))
        {
            search_book(fin, fout, T1);
        }
        else if(!strcmp("list_author", comanda))
        {
            list_author(fin, fout, T2);
        }
        else if(!strcmp("search_by_author", comanda))
        {
            search_by_author(fin, fout, T2);
        }
    }

    /* eliberare memorie */
    free(comanda);
    FreeTrie(T1, FreeBook);
    FreeTrie(T2, FreeT2info);
    fclose(fin);
    fclose(fout);

    return 0;
}