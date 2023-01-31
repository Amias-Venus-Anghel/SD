/* ANGHEL Ionela-Carmen - 312CB */

Punctajul obtinut la teste la rularea pe calculatorul propiu: 135/135 | 20/20

Arhiva contine fisierele:
tema2.c
netflix.c netflix.h
lista.c lista.h
coada.c coada.h coada_functii.h
stiva.c stiva.h stiva_functii.h

 ____________
// tema2.c //
************
-fisiereul principal
-contine functia main si functia de comparare 2 elemente

/* CmpSrl */
-primeste ca parametrii doi pointeri de tip void
-converteste si compara informatile: un sir de caractere si un element de tip SerialQ
-returneaza 1 daca sirul de caractere si numele serialului corespund, altfel 0

/* main */
-primeste parametrii din lista de comanda si extrage numele fisierelor
-se aloca memorie pentru parametrul de citire a comenzii si se deschid fisierele cu 
modul adecvat
-se declara categoriile si sectiunile necesare ca liste, cozi si stive
-cat timp exista comenzi in fisier, este scanata comanda si se fac prelucrarile necesare
-pentru comanda "add": se creaza serialul si se insereaza in categoria ceruta, conform 
id-ului
-pentru comanda "show": se citeste numele sectiunii de afisat si se apeleaza afisarea
acesteia
-pentru comanda "add_sez": se citeste numele serialului de prelucrat si se cauta acesta in 
fiecare sectiune; daca este gasit se insereaza un nou sezon la acesta
-pentru comanda "add_top": se creaza serialul si se insereaza in top10, apoi se afiseaza
lista de seriale din top
-pentru comanda "later": se citeste numele si se cauta si extrage serialul din categoria 
in care se afla si se introduce in coada later
-pentru comanda "watch": se citeste numele si durata de vizionare si se extrage serialul
din categoria in care se afla; daca este gasit, se adauga in stiva watching si se
micsoreaza durata ramasa din serial, iar daca aceasta devine nula sau negativa, serialul
este mutat in stiva history
-se distrug listele, cozile si listele folosite si se inchid fisierele de citire si iesire

 ______________
// netflix.h //
**************
-fisier header care contine bibliotecile si headerele pentru liste, cozi si stive generice
-este definita structura de serial care contine id, nume, rating, numarul de sezoane, 
coada serial care contine serialul propiu-zis, si durata totala ramasa de vizionare din
serial
-este definita structura de sezon care contine numarul de episoade si coada de episoade
propiu-zisa
-sunt definite SCel si SRL pentru scriere mai rapida in cadrul functilor de prelucrare
-sunt declarate prototipurile functilor de prelucrare folosite in tema2.c

 ______________
// netflix.c //
**************
-fisier sursa care contine functiile principale de prelucrare a serialelor
-contine headerul netflix.h

/* InitSerial */
-functie care initializeaza un serial nou
-primeste ca parametrii id-ul, numele, ratingul si numarul de sezoane ale serialului
-se aloca spatiu pentru serial si pentru coada de sezoane si se atribuie valori campurilor
structurii

/* CreareSerial */
-functie care citeste si construieste un nou serial
-primeste ca parametru fisierul de citire
-se citesc datele serialului: id, nume, rating, nr de sezoane
-se initializeaza un serial nou
-pentru fiecare sezon se citeste numarul de episoade si se aloca spatiu pentru sezon
-se initializeaza coada sezon si sunt citite si inserate minutele fiecarui episod
-se mareste durata totala a serialului pentru fiecare episod inserat
-se returneaza serialul creat sau NULL daca crearea esueaza

/* InsCategorie */
-functie care adauga serialul nou creat intr-o categorie
-primeste ca parametrii un serial, o lista (categoria) si fisierul de iesire
-daca categoria este goala, sau ratingul primului element din lista este mai mic decat
ratingul serialului dat, sau ratingurile sunt egale iar ordonare dupa nume cere adaugarea 
inainte, este adaugat noul serial pe prima pozitie a categoriei
-altfel se parcurge lista categoriei si se cauta prima pozitie potrivita pentru inserarea 
serialului
-se retine celula dupa care se va insera si numarul de ordine al pozitiei
-se insereaza serialul la pozitia corespunzatoare gasita

/* Add_sez */
-functie care adauga un nou sezon unui serial dat
-primeste ca parametrii serialul de modificat si fisierul de citire
-se aloca spatiu pentru un nou sezon si se insereaza in coada serialului
-se citesc numarul de episoade si episoadele si se insereaza in sezon
-numarul de sezoane ale serialului creste
-functia nu returneaza nimic

/* Add_top */
-functie care adauga un serial in top10
-primeste ca parmetrii serialul si lista top10
-insereaza serialul la pozitia data in lista, unde pozitia de inserare este citita si 
retinuta in campul id al serialului
-daca lungimea listei top10 depaseste 10, este eliminat ultimul element din lista

/* FreeSerial */
-functie de eliberare a memoriei alocata unui serial
-primeste ca parametru de intrare un pointer void la serialul de eliberat
-se convereteste la tipul SerialQ 
-se elibereaza spatiul alocat numelui
-cat timp coada serial nu este vida, se extrage fiecare element si se distruge coada de 
episoade (adica fiecare sezon) si se elibereaza spatiul alocat structurii sezon
-se elibereaza spatiul alocat serialului.

/* AfiCateg */
-functie care afiseaza informatia de tip SerialQ
-primeste ca parametru un pointer de tip de void si fisierul de iesire
-face afisarea corespunzatoare

/* Find_Q */
-functie care cauta si returneaza adresa informatiei cautate (sau NULL) intr-o coada 
fara a o elimina din coada data
-primeste adresa cozii, referinta la elementul cautat (in cazul nostru numele serialului)
si functia de comparare
-se initializeaza o noua coada
-cat timp coada originala are elemente, se extrage fiecare element si se compara, daca se
gaseste elementul cautat i se retine adresa
-toate elementele sunt adaugate in noua coada
-coada initiala este distrusa si adresa ei se muta la coada nou creat(recompusa)

/* Find_S */
-functie identica cu Find_Q, specializata pentru o stiva, urmeaza aceasi pasi si 
returneaza adresa elementului cautat sau NULL
-pentru reconstruirea stivei se rastoarna stiva noua in stiva veche si se distruge stiva
veche

/* Get_Q */
-functie care extrage si returneaza adresa elementului cautat dintr-o coada (sau NULL)
-primeste ca parametrii coada, referinta la elementul cautat(numele serialului) si functia
de comparare
-urmeaza pasi identici cu functia Find_Q, cu diferenta ca la gasirea elementului cautat
acesta nu este reintrodus in noua coada

/* Get_S */
-functie care extrage si returneaza adresa elementului cautat dintr-o coada (sau NULL)
-functie identica cu Get_Q, particularizata pentru o stiva in loc de coada

 ____________
// lista.h //
************
-fisier header pentru functiile de prelucrare a listelor generice simplu inlantuite
-este definita structura de celula si lista
-sunt definite tipurile generice de functii pentru comparare, eliberare si afisare a 
elementelor
-sunt definite prototipurile functilor de prelucrare a listelor

 ____________
// lista.c //
************
-fisier sursa ce contine functile de prelucrare a unei liste generice simplu inlantuite

/* InsLGinc */
-functie care insereaza un element la inceputul listei
-primeste adresa listei si a elementului de inserat
-creaza o celula si o ataseaza la lista
-returneaza 1/0 pentru inserare reusita/nereusita

/* InsLGdupa */
-functie care insereaza un element dupa o celula data ca parametru
-primeste ca parametrii celula dupa care se insereaza si elementul de inserat
-creaza o celula si reface legaturile pentru includerea noii celule in lista\
-returneaza 1/0 pentru inserare reusita/nereusita

/* InsLGpoz */
-functie care insereaza un element dat la o pozitia ceruta in lista
-primeste adresa listei, a elementului de inserat si pozitia de inserare
-se parcurge lista pana la pozitia ceruta si se insereaza elementul
-returneaza acelasi rezultat ca functia InsLGinc 

/* ElimUltim */
-functie care elimina ultima celula a listei
-primeste lista de modificat si functia de eliberare a informatiei din lista
-se parcurge lista pana la final, retinandu-se ultimul element
-se modifica legaturile si se elibereaza memoria

/* DistrLG */
-functie care ditruge o lista
-primeste adresa listei si functia de eliberare a informatiei
-pentru fiecare celula din lista se muta inceputul listei si se elibereaza memoria celulei
"aux"

/* LungimeLG */
-functie care calculeaza lungimea unei liste
-primeste adresa listei
-se parcurge lista, incrementandu-se un contor
-se returneaza contorul

/* AfiLG */
-functie de afisare a listei
-primeste adresa listei, functia de afisare si fisierul de iesire
-pentru fiecare element din lista se apeleaza functia de afisare a informatiei
-cat timp in lista mai urmeaza un element de afisat, se adauga ","

/* Find_elem */
-functie care cauta si retuneaza adresa elementului cautat in lista
-primeste ca parametrii lista, referinta la elementul cautat si functie de comparare
-pentru fiecare element din lista se verifica identitatea informatiei cu referinta
-daca se gaseste se va returna adresa la informatie, altfel NULL

/* Extr_elem */
-functie care extrage un element din lista
-primeste adresa listei, referinta la elementul cautat si functia de comparare
-daca lista este vida sau nu se gaseste elementul cautat se returneaza NULL
-se parcurge lista si se compara elementele, daca se gaseste  elementul cautat se retine
adresa celului si se refac legaturile pentru eliminare celului din lista
-se elibereaza memoria alocata celului si se returneaza adresa informatiei

 ____________
// coada.h //
************
-fisier header in care sunt definite structura de coada si functii rapide pentru usurarea
scrierii functilor de prelucrare
-fisierul sursa principal nu are acces la acest header, deci nici la modul de implementare
a cozilor

 ____________________
// coada_functii.h //
********************
-fisier header pentru coada
-contine bibliotecile necesare si prototipurile functilor de prelucrare a cozilor generice
ce pot fi accesate in alte fisiere

 ____________
// coada.c //
************
-fisier sursa ce contine functile de prelucrare a unei cozii generice implementate cu
liste generice simplu inlantuite

/* InitQ */
-functie care initializeaza o coada
-primeste ca parametru dimensiunea unui element si returneaza coada creata
-se aloca memorie pentru structura de coada si se initializeaza inceputul si sfarsitul
cozii cu NULL

/* InsQ */
-functie de inserare a unui element in coada
-primeste ca parametrii o coada si adresa elementului de inserat
-se creaza o noua celula a carei informatie este elementul dat, elementul este alocat 
pentru fiecare inserare separat
-daca coada este vida se seteaza inceutul si finalul la noua celula, altfel finalul
se muta la noua celula
-returneaza 1/0 pentru inserare reusita/esuata

/* ExtrQ */
-functie de extragere a unui element din coada
-primeste ca parametrii coada si adresa la care se va pastra elementul extras
-daca coada are mai multe elemente se deplaseaza inceputul cozii
-daca coada are un singur element se seteaza inceputul si finalul cozii la NULL
-se elibereaza memoria alocata celulei si se retine adresa informatiei
-returneaza 1/0 pentru extragere reusita/esuata

/* ResetQ */
-functie de resetare a cozii
-primeste coada si functia de eliberare
-pentru fiecare element se elibereaza informatia si celula
-inceputul si sfarsitul cozii sunt setate la NULL

/* DistrQ */
-functie de distrugere a cozii
-primeste adresa cozii de distrus si functia de eliberare
-reseteaza coada si elibereaza memoria cozii

/* LgQ */
-functie care returneaza lungimeacozii
-primeste ca parametru o coada si o parcurge cu incrementarea unui contor

/* AfiQ */
-functie de afisare a cozii
-primeste coada, functia de afisare si fisierul de iesire
-se afiseaza cu ajutorul functiei de afisare a listelor generice simplu inlantuite

/* VidaQ */
functie care returneaza 1/0 pentru coada vida sau nu

 ____________
// stiva.h //
************
-fisier header in care sunt definite structura de stiva si functii rapide pentru usurarea
scrierii functilor de prelucrare
-fisierul sursa principal nu are acces la acest header, deci nici la modul de implementare
a stivelor

 ____________________
// stiva_functii.h //
********************
-fisier header pentru stiva
-contine bibliotecile necesare si prototipurile functilor de prelucrare a stivelor
generice ce pot fi accesate in alte fisiere

 ____________
// stiva.c //
************
-fisier sursa ce contine functile de prelucrare a unei stive generice implementate cu
liste generice simplu inlantuite

/* InitS */
-functie care initializeaza o stiva
-primeste ca parametru dimensiunea unui element si returneaza stiva creata
-se aloca memorie pentru structura de stiva si se initializeaza varful stivei cu NULL

/* Push */
-functie de inserare a unui element in stiva
-primeste ca parametrii o stiva si adresa elementului de inserat
-se creaza o noua celula a carei informatie este elementul dat, elementul este alocat 
pentru fiecare inserare separat
-varful stivei se muta la noua celula
-returneaza 1/0 pentru inserare reusita/esuata

/* Pop */
-functie de extragere a unui element din stiva
-primeste ca parametrii stiva si adresa la care se va pastra elementul extras
-se retine adresa informatiei din varf si se modifica acesta apoi se elibereaza memoria 
alocata celulei
-returneaza 1/0 pentru extragere reusita/esuata

/* ResetS */
-functie de resetare a stivei
-primeste stiva si functia de eliberare
-pentru fiecare element se elibereaza informatia si celula
-varful stivei este setat la NULL

/* DistrS */
-functie de distrugere a stivei
-primeste adresa stivei de distrus si functia de eliberare
-reseteaza stiva si elibereaza memoria acesteia

/* Rastoarna */
-functie care rastoarna stiva sursa in stiva destinatie
-primeste ca parametrii doua stive
-se verifica identitate dimensiunii elementelor si existenta elementelor in stiva sursa
-fiecare element din stiva sursa este mutat in stiva destinatie
-varful stivei sursa devine NULL

/* AfiS */
-functie de afisare a stivei
-primeste stiva, functia de afisare si fisierul de iesire
-se afiseaza cu ajutorul functiei de afisare a listelor generice simplu inlantuite

/* VidaS */
-functie care returneaza 1/0 pentru stiva vida sau nu











