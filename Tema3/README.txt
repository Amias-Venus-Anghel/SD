/* ANGHEL Ionela-Carmen - 312CB */

===============================================================================
				TEMA 3 - SD
===============================================================================
	punctaj obtinut la rularea pe calculatorul propiu: 
 							Total: [110/135]
 							Bonus: [15.0/20.0]
===============================================================================

Arhiva contine 5 fisiere sursa/header:
tema3.c 
carte.h
carte.c
trie.h
trie.c

===============================================================================
				tema3.c
===============================================================================
 
	Fisierul sursa contine functile principale de prelucrare 
corespunzatoare fiecarei comenzi (cu exceptia comenzii delete care nu a fost
implementata)
 ______________
/ CharToIndex /
**************
- functie care primeste ca parametru un caracter char si returneaza un numar
intre 0 si ALPHABET_SIZE corespunzator caraterului dat
- se construieste alfabetul si il parcurc cautand caracterul dat

 _____________
/ FreeT2info /
*************
- functie care elibereaza informatia din frunzele trie-ului T2 (informatia este
de tipul ATrie)
- converteste informatia la tipul real si elibereaza (fara informatie) 
structura primita (informatia este retinuta ca pointer spre o structura ABook,
pointer care se gaseste atat in T1 cat si in fiecare trie din T2, la eliberarea
lui T1 se elibereaza si informatile, iar la eliberarea lui T2 nu mai exista
informatii de eliberat, asa ca se distruge doar structura trie)

 ___________
/ AfiAutor /
***********
- functie care afiseaza numele autorului
- primeste ca parametru un pointer void la un arbore trie corespunzator 
autorului, si fisierul de iesire
- parcurge una din ramurile arborelui pentru ajunge la informatia de tip ABook
pentru afisarea numelui autorului

 ___________
/ add_book /
***********
- functie care citeste si adauga in arborii T1 si T2 o noua carte
- se citeste cartea si se cauta in T1, daca aceasta exista deja se va elibera
memoria alocata cartii
- daca cartea nu exista, se va adauga in T1
- se cauta numele autorului in T2, daca este gasit se obtine arborele trie 
corespunzator si se insereaza in el cartea
- daca numele autorului nu exista in T2, se creaza un nou arbore trie si este
inserat in T2

 ______________
/ search_book /
**************
- functie care cauta o carte in T1
- primeste fisierele de intrare si iesire si arborele T1
- se citeste randul si se cauta caracterul "~" pentru verificarea cererii
de autocompletare
- daca nu se gaseste, se obtine titlu (eliminarea spatiului din fata sa si a
new-line-ului) si se obtine informatia cautat dupa titlu in T1, afisandu-se
mesajul corespunzator
- daca se cere autocompletarea se obtine semi-titlul si se apeleaza functia
de cautare dupa prefix; daca nu se afiseaza nici o carte se afiseaza mesajul
corespunzator
- se elibereaza memoria sirului de citire

 _____________
/ list_autor /
*************
- functie care cauta o carte in T2
- primeste fisierele de intrare si iesire si arborele T2
- se citeste randul si se cauta caracterul "~" pentru verificarea cererii
de autocompletare
- daca nu se gaseste caracterul, se obtine numele autorului cautat si se cauta
arborele trie specific lui, apoi se afiseaza mesajul corespunzator
- daca se cere autocompletarea, se obtine semi-autorul si se cauta in T2 dupa
prefix, daca nu se afiseaza nici un autor, se afiseaza mesajul corespunzator
- se elibereaza sirul de citire

 ___________________
/ search_by_author /
*******************
- functie care cauta dupa autor
- primeste fisierele de intrare, iesire si arborele T2
- se citeste linia si se verifica daca se cere autocompletare prin cautarea 
caracterului "~"
- daca nu se cere autocompletare, se obtine autorul si titlul si se cauta in T2
dupa autor, obtinandu-se arborele Tautor
- daca autorul se afla in T2, se obtine Tautor corespunzator si se cauta in el
dupa titlul cartii cu afisarea mesajului corespunzator
- daca autorul nu se afla in T2, se obtine Tautor = NULL si se afiseaza mesajul
corespunzator
- daca se gaseste caracterul "~", se cere autocompletare
- se cauta caracterul ":" pentru identificarea autocompletarii la titlu sau la
autor
- daca nu se gaseste, se autocompleteaza la autor in mod similar ca mai devreme
- daca se gaseste, se citeste autorul si semi-titlul si se obtine Tautor 
corespunzator autorului dat, apoi se cauta dupa prefix in Tautor (daca este
diferit de NULL) cu afisarea mesajului corespunzator
- se elibereaza sirul de citire

 _______
/ main /
*******
- se obtin fisierele de intrare si iesire si se deschid
- se aloca memorie pentru citirea comenzii 
- se creaza arborii trie T1 si T2
- se identifica comanda citita si se apeleaza functia corespunzatoare
- se elibereaza memoria alocata si se inchid fisierele

===============================================================================
				carte.h
===============================================================================
-fisier header care contine bibliotecile necesare, structura cartii si 
prototipurile functilor
- structura ABook contine 2 siruri de caractere (titlul si autorul) si 2 numere
intregi ( ratingul si nr de pagini)
- este definit si MAX, utilizat pentru alocarea de memorie

===============================================================================
				carte.c
===============================================================================

 ___________
/ ReadBook /
***********
- functie care citeste si contruieste o carte
- primeste fisierul de intrare
- citeste linia si aloca memorie pentru fiecare sir, in care se copiaza 
informitia corespunzatoare citita
- se aloca memorie cartii book si se atribuie elementelor sale valorile citite
- se returneaza cartea

 __________
/ AfiBook /
**********
- functie care afiseaza informatile unei carti
- primeste fisierul de iesire si structura cartii

 ___________
/ FreeBook /
***********
- functie care elibereaza memoria alocata unei carti
- primeste pointer void la structura, o converteste si elibereaza sirurile de 
caractere si structura

 __________
/ AfiBouk /
**********
- functie care primeste fisierul de iesire si pointer void la strunctura si 
afiseaza titlul cartii

===============================================================================
				trie.h
===============================================================================
- fisier header care contine: bibliotecile necesare, definirea lui 
ALPHABET_SIZE, definirea structurii ATrie, definirea prototipurilor functilor
- structura ATrie contine un vector de copii de tip ATrie cu lungimea 
corespunzatoare alfabetului dat, un bool isEndOfWord care este adevarat daca
nodul corespunzator contine o informatie, si pointer void la informatia
corespunzatoare (in cadrul implementarii informatia va fi fie de tip ABook, fie
de tip ATrie, de aceea am preferat informatia generalizata)

===============================================================================
				trie.c
===============================================================================
- fisier sursa care contine functile de prelucrare a structurii ATrie

 __________
/ GetNode /
**********
- functie care creaza si returneaza un nod nou
- se aloca memorie si se initializeaza vectorul de copii si informatia cu NULL

 _________
/ Insert /
*********
- fucntie de inserare in arbore
- primeste radacina, sirul de caractere dupa care se face inserarea(key),
functia de calcularea a indexului si pointer la informatia de inserat
- pentru fiecare caracter al sirului key se verifica daca acesta exista in 
arbore si se creaza daca nu exista
- se introduce informatia in frunza, si se marcheaza corespunzator

 ______
/ Get /
******
- functie care cauta si returneaza pointer la informatia cautata
- primeste arborele, cheia dupa care se cauta si functia de calculare a 
indexului
- se parcurge asemanator ca la inserare
- daca unul dintre caractere sirului de cautat nu este gasit, se returneaza
NULL
- daca dupa parcugerea sirului complet, frunza contine informatie, se va 
returna, altfel se intoarce NULL

 ___________
/ FreeTrie /
***********
- functie care elibereaza un arbore trie si informatile din el
- primeste arborele si functia de eliberare a informatiei
- se parcurge recursiv arborele si se elibereaza informatia daca exista, apoi
se elibereaza nodul

 ___________
/ free_all /
***********
- functie similara lui FreeTrie, care elibereaza un arbore, fara a elibera
informatia
- in cadrul implementarii, retin ca informatie pointerul spre structura cartii,
structura identica pentru T1 si fiecare arbore din T2. Dupa eliberarea lui T1,
nu mai raman informatii de eliberat, fiind necesara numai distrugerea nodurilor
arborilor din T2

 __________
/ AfiTrie /
**********
- functie care afiseaza elementele din trie
- primeste radacina, functia de afisare si fisierul de iesire
- se parcurge recursiv arborele (asemenea parcurgerii de eliberare) si se 
afiseaza informatile existente

 ______________
/ AfiSemiTrie /
**************
- functie care afiseaza doar primele N elemente din arbore
- primeste radacina, functia de afisare, pointer la numarul de afisari si
fisierul de iesire
- functia intoarce numarul de afisari efectuate (maxim N)
- daca numarul de afisari ajuge la 0 sau radacina e NULL, se intoarce 0
- daca root contine informatie se afiseaza aceasta si se scade valoarea de la
N, creste numarul de afisari efectuate
- pentru fiecare copil al lui root se apeleaza functia, si se mareste nr de 
afisari daca este cazul 
- se returneaza numarul de afisari efectuat

 ___________
/ SrcPrefx /
***********
- functie care cauta dupa prefixul dat si afiseaza primele 3 elemente gasite
- returneaza numarul de afisari efectuat
- primeste arborele in care se cauta, preficul cautat(key), functia de 
calculare a indexului, functia de afisare a informatiei si fisierul de iesire
- se parcuger arborele dupa key
- daca un caracter al lui key nu  este gasit se intrerupe parcurgerea
- daca s-au parcurs toate caracterele lui key si s-a trecut de root, se 
apeleaza functia de AfiSemiTrie si se retine numarul de afisari returnat
- daca nu au fost parcurse toate caracterele lui key, se returneaza 0, altfel
se returneaza numarul de afisari efectuat