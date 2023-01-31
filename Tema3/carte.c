/* ANGHEL Ionela-Carmen - 312CB */

#include "carte.h"

/* citire si creare carte */
ABook ReadBook(FILE* fin)
{
    char* line = NULL;
    size_t len = 0;
    getline(&line, &len, fin);
    char* temp = NULL;

    char* titlu = (char*)malloc(MAX);
    if(!titlu)
        return NULL;
    temp = strtok(line+1, ":");
    strcpy(titlu, temp);

    char* autor = (char*)malloc(MAX);
    if(!autor)
    {
        free(titlu);
        return NULL;
    }
    temp = strtok(NULL, ":");
    strcpy(autor, temp);

    int rating, nrpag;
    temp = strtok(NULL, ":");
    rating = atoi(temp);
    temp = strtok(NULL, ":");
    nrpag = atoi(temp);

    free(line);

    ABook book = (ABook)malloc(sizeof(Book));
    if(!book)
        return NULL;
    book->autor = autor;
    book->titlu = titlu;
    book->rating = rating;
    book->nrpag = nrpag;
    return book;

}

/* fucntie de afisare a unei cartii */
void AfiBook(ABook book, FILE* fout)
{
    fprintf(fout, "Informatii recomandare: ");
    fprintf(fout, "%s, %s, ", book->titlu, book->autor);
    fprintf(fout, "%d, %d\n", book->rating, book->nrpag);
}

/* funcite eliberare carte */
void FreeBook(void* info)
{
    if(!info)
        return;
    ABook book = (ABook)info;

    free(book->autor);
    free(book->titlu);
    free(book);
    info = NULL;
}

/* functie de afisare a titlului */
void AfiBouk(void* info, FILE* fout)
{
    fprintf(fout, "%s\n", ((ABook)info)->titlu);
}
