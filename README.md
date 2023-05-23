# TEMA LANPARTY
Consider ca am facut o implementare de nivel mediu, nici prea sofisticata, dar nici prea naiva.
Pentru inceput, in functia main am lucrat cu argumente in linia de comanda in urmatoarea ordine: LanParty - executabilul; c.in - fisierul care imi dicteaza executarea task-urilor; d.in - fisierul cu datele necesare realizarii task-urilor; r.out - fisierul folosit ca 'output'. Astfel, dupa ce am salvat intr-un vector ordinea in care se vor executa functiile ce desemneaza fiecare task, am implementat o structura de tip 'if' care va face acest lucru.
Am declarat diverse structuri: Player - structura data deja in tema, Team - contine numele echipei, numarul de jucatori din echipa, punctajul echipei si un vector 'PlayerArray' in care se salveaza fiecare jucator. TeamsQueue - element dintr-o coada in care salvez doua echipe ce se vor confrunta. StackNode - nodul de inceput al unei stive care contine echipele castigatoare sau pierzatoare. TreeNode - nodul de inceput al unui arbore binar sau AVL.

## Task 1
Dupa cum a fost cerut in cerinta, am folosit o lista simplu inlantuita in care am salvat echipele din fisier. Am lucrat cu o structura auxiliara de tip Team*(Team este o structura declarata in header in care salvez echipele) in care citeam fiecare detaliu din fisier. Tin sa mentionez ca unele denumiri de echipe aveau spatii la sfarsit, asa ca am tratat si acest caz. Dupa ce terminam de salvat toate datele necesare in auxiliar, il adaugam imediat la inceputul listei. La final, am afisat lista si am facut eliberarile de memorie necesare.

## Task 2
Pentru inceput, stim ca in fiecare fisier, primul numar este numarul total de echipe, asa ca l-am salvat intr-o variabila. Am facut acest lucru pentru ca, dupa aceea, sa utilizez o alta functie 'PowOf2' care imi calculeaza cea mai mica putere a lui 2 imediat mai mica decat numarul salvat anterior. Dupa aceea, intr-un 'while' verific daca numarul de echipe total este mai mic decat cel calculat cu functia 'PowOf2', si daca da, imi calculeaza media intr-un vector pentru fiecare echipa si, din acel vector, aflu valoarea minima. In pasul urmator parcurg lista si cand echipa are punctaj egal cu minimul, o elimin si restabilesc conexiunile.

## Task 3
Aici, pentru a evita problemele cu adresele comune, am lucrat cu 2 cozi diferite. Asadar, creez cozile normal cu functia din curs si le afisez, apoi, cat timp cozile mea salveaza echipele (in fiecare element al cozii salvez cate 2 echipe care vor concura), le verific punctajul si apoi le adaug in stivele corespunzatoare. Cele care se afla in stiva de castigatori vor avea punctajul marit de fiecare data cu un punct, respectiv si jucatorii din lot. Fac acest lucru intr-o structura de tip 'while', pana ajung la ultimele 8 meciuri. Din acest moment, se poate intelege ideea pentru care am ales sa lucrez cu doua cozi simultan. Cand am ajuns la ultimele 8 meciuri, continui sa lucrez doar cu una, astfel incat sa salvez echipele pentru urmatorul task, fara sa modific vreun punctaj. Continui, dupa cum am specificat, cu o singura coada pana cand aflu echipa castigatoare. Evident, de fiecare data cand realizez stivele de castigatori si pierzatori, dupa ce termin de a le folosi la fiecare pas din 'while', le eliberez memoria. Tin sa mentionez ca am realizat o functie de tip 'update' unde salvez datele de la ultimele 8 echipe ramase, fara punctaje modificate, unde mai apoi o utilizez pentru a modifica punctajul echipelor aferente.

## Task 4
Pentru realizarea acestui task, aveam nevoie de echipele salvate la task-ul anterior. Asadar, am lucrat cu coada salvata anterior dupa cum am mentionat si am creat o functie care imi transmite elementele dintr-o coada intr-o lista. Dupa ce am facut acest lucru, am observat ca lista este afisata in ordine inversa, deci am creat o alta functie 'reverseList' care imi inverseaza elementele listei. Apoi, totul este foarte simplu, deoarece am creat o functie asemanatoare cu cea din curs, unde iau in considerare si faptul ca unele echipe au acelasi punctaj, comparandu-le dupa nume si adaugandu-le in arborele binar.

# Task 5
Am facut ceva asemanator task-ului 4, mai exact am parcurs arborele salvat anterior in 'inordine' si am salvat elementele intr-o lista. Lista aceasta s-a dovedit a fi, din nou, pe dos, asa ca am inversat-o. Dupa aceea, am creat o functie insert care se foloseste de toate rotatiile prezente in curs, inclusiv cele duble. Asemenea task-ului anterior, introduce noduri recursiv si echilibreaza arborele instant. In momentul in care se intalnesc doua echipe cu acelasi punctaj, se vor lua dupa nume, in ordine descrescatoare.






Pentru folosirea checker-ului, se va folosi urmatoarea comanda:
```shell
./checker.sh
````



