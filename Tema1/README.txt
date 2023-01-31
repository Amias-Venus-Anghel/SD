/* ANGHEL Ionela Carmen - 312CB */	
 ____________
// FISIERE //
************
	
Tema este implementata cu ajutorul a 3 fisiere sursa: 
* fisierul principal de prelucrare
* fisier cu functile de prelucrare ale tabelei hash
* fisier header 

 ____________
// tema1.h //
************

Fisierul contine definirea strucurilor folosite, includerea 
bibliotecilor, definirea si declaratia functilor

Structura folosita ca tip al informatior din tabela este adresaIP
si contine 2 siruri de caractere

 ____________
// tema1.c //
************

Fisierul sursa contine functia main si functii particulare 
pentru prelucrarea informatiei de tip adresaIP


/* codHash */
-primeste un parametru tip = 1/0
-tip este 1 daca aflam codul unui element de tip adresaIP si 0 
daca aflam codul unui sir de caractere
- calculeaza codul hash pentru sir  
- obtinem lungimea sirului si calculam suma valorilor caracterelor
sale in variabila cod
-returneaza cod % M, unde M reprezinta numarul de bucket-uri
corespunzator tabelei hash

/* compKey */
-primeste 2 pointeri si un intreg tip
-tip este 1 daca se compara un element de tip adresaIP si un sir
-tip este 0 daca se compara 2 elemente de tip adresaIP
-compara sirul cu adresa retinuta de elementul primit
-returneaza 0 daca sunt identice

/* AlocareEl */
-aloca si creaza noul element pentru a fi inserat in tabela hash
-returneaza un pointer NULL la elementul creat

/* AfiEl */
-functie de afisare pentru un element de tip adresaIP

/* FrAdresa */
-functie de eliberare a emoriei pentru un element de tip adresaIP

/* main */
-extrage din parametrii primiti in linia de comanda fisierele de 
intrare si iesire si dimensiunea tabelei.
-se initializeaza noua tabela hash: tabela
-cat timp se poate citi din fisierul de intrare se citeste comanda
-aloc memorie pentru int=formatile ce vor fi citite: link si adresa
-pentru comanda "put" se citesc sirurile link si adresa, se creaza
noul element ce va fi inserat si se insereaza in tabela; daca acesta
exista deja se va elibera memoria alocata elementului
-pentru comanda "get" se citeste sirul cautat si se afiseaza 
valoare gasita sau NULL daca nu se gaseste
-pentru comanda "remove" se citeste sirul cautat si se sterge
din tabela
-pentru comanda "find" se citeste sirul cautat si se cauta in tabela
-pentru comanda "print" se apeleaza functia de afisare
-pentru comanda "print_bucket" se citeste codul cerut si se apeleaza
functia de afisarea
-se elibereaza memoria alocata lui link si adresa
-se elibereaza memoria alocata pentru comanda, se inchid fisierele
si se elbereaza memoria alocata tabelei hash


 ____________________
// tema1-functii.c //
********************

Fisierul sursa contine functiile de prelucrare a tabelei hash

/* InitHash */
- aloca spatiu pentru tabela hash, vectorul de liste si atribuie
campurilor tabelei valorile corespunzatoare
-se returneaza tabela hash goala

/* Put */
-primeste tabela, un pointer la elementul de inserat si functie 
de comparatie
-se obtine codul hash al elementului si se parcurge lista
corespunzatoare
-daca se gaseste elementul, functia retuneaza 0
-daca nu se gaseste elementul, se retine in aux pozitia in urma
careia trebuie introdus noul element
-daca aux ramane NULL, elementul trebuie introdus pe prima pozitie
a listei
-se verifica daca noul element este si primul element introdus 
in lista pentru crearea corecta a legaturilor
-functia returneaza 1 dupa ce s-a efectuat inserarea

/* PrintH */
-primeste tabela, functia de afisare si fisierul de afisare
-pentru fiecare bucket din vectorul de liste se afiseaza toate
elementele

/* PrintBucket */
-primeste tabela, codul bucketului de afisat, functia de afisare a
elementelor din tabela si fisierul de iesire
-daca codul depaseste dimensiunea vectoruui se iese din functie
-daca lista nu contine elemente se afiseaza VIDA si se iese din
functie
-altfel se parcuge lista si se afiseaza elementele

/* Get */

-obtinem codul hash al elementului cautat
-daca lista este vida se iese din functie
-altfel se parcurge lista si se cauta elementul, daca se gaseste
se retuneaza adresa informtiei
-daca nu se gaseste se va returna NULL

/* Find */
-primeste tabela, sirul cautat, functia de comparare si fisierul
de iesire
-se obtine codul hash al sirului cautat si se verifica daca lista
corespunzatoare are elemente
-daca lista e nevida se cauta elementul si se afiseaza rezutatul
corespunzator

/* Remove */
-primeste tabela, sirul cautat, functia de comparare si functia de
eliberare a elementelor
-se obtine codul hash si se verifica lista corespunzatoare
-daca lista e nenula si se gaseste elemntul, se refac legaturile
si se elibereaza memoria alocata
-daca este eliminat singurul element al listei, se seteaza valoarea
NULL
-daca este primul element, se modifica inceputul listei

/* DistrTH */
-primest pointer la adresa tabelei si functia de eliberare 
a informatiei
-parcurge fiecare pozitie a vectorului si elibereaza fiecare lista
-se elibereaza memoria alocata vectorului si apoi a tabelei
-se seteaza pointerul la adresa cu NULL




















