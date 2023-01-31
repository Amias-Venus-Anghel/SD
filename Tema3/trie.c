/* ANGHEL Ionela-Carmen - 312CB */
#include "trie.h"

/* creaza un nod nou de trie */
ATrie GetNode()
{
    ATrie pNode = NULL;

    pNode = (ATrie)malloc(sizeof(Trie));

    if (pNode)
    {
        int i;

        pNode->isEndOfWord = false;

        for (i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;

        pNode->info = NULL;
    }

    return pNode;
}

/* inserare in trie */
void Insert(ATrie root, char *key, TCmp idx, void* info)
{
    int level;
    int length = strlen(key);
    int index;

   ATrie pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = idx(key[level]); /* calculex indexul */
        if (!pCrawl->children[index])
            pCrawl->children[index] = GetNode();

        pCrawl = pCrawl->children[index];
    }

    pCrawl->isEndOfWord = true;
    pCrawl->info = info; /* info alocat separat pe fiecare element */
}

/* returneaza informatia cautata dupa key sau NULL */
void* Get(ATrie root, char* key, TCmp idx)
{
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;
    for (level = 0; level < length; level++)
    {
        index = idx(key[level]);
        if(!pCrawl->children[index])
            return NULL;

        pCrawl = pCrawl->children[index];
    }

    if(pCrawl->isEndOfWord)
        return pCrawl->info;

    return NULL;
}

/* eliberare trie cu informatie */
void FreeTrie(ATrie root, Tfr fr)
{
    if(!root)
        return;

    if(root->isEndOfWord)
        fr(root->info);

    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
        FreeTrie(root->children[i], fr);
    }
    free(root);
}

/* eliberare trie fara informatie */
void free_all(ATrie root)
{
     if(!root)
        return;

    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
        free_all(root->children[i]);
    }
    free(root);
}

/* afisare trie */
void AfiTrie(ATrie root, Tafi afi, FILE* fout)
{
    if(!root)
        return;

    if(root->isEndOfWord)
        afi(root->info, fout);

    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
       AfiTrie(root->children[i], afi, fout);
    }
}

/* functie care afiseaza doar primele N elemente din trie */
int AfiSemiTrie(ATrie root, Tafi afi, int* N, FILE* fout)
{
    int afisari = 0;
    if(!root || *N <= 0)
        return 0;

    if(root->isEndOfWord)
    {
        afi(root->info, fout);
        (*N)--;
        afisari++;
    }

    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
       afisari+= AfiSemiTrie(root->children[i], afi, N,  fout);
    }

    return afisari;
}

/* returneaza nr de afisari cu prefixul dat (key = prefix) */
int SrcPrefx(ATrie root, char* key, TCmp idx, Tafi afi, FILE* fout)
{
    ATrie pCrawl = root;
    int length = strlen(key);
    int i;
    for (i = 0; i < length; i++)
    {
        int index = idx(key[i]);
        if(pCrawl->children[index])
            pCrawl = pCrawl->children[index];
        else
            break;
    }

    int afisari = 0;
    if(pCrawl !=  root && i == length)
    {
        int N = 3;
        afisari  = AfiSemiTrie(pCrawl, afi, &N, fout); /* N primeste numarul de afisari efectuate */
    }

    return afisari;
}
