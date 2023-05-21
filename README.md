# TEMA LANPARTY
Pentru folosirea checker-ului, se va folosi urmatoarea comanda:

Consider ca am facut o implementare de nivel mediu, nici prea sofisticata, dar nici prea naiva.
Pentru inceput, in functia main am lucrat cu argumente in linia de comanda in urmatoarea ordine: LanParty - executabilul; c.in - fisierul care imi dicteaza executarea task-urilor; d.in - fisierul cu datele necesare realizarii task-urilor; r.out - fisierul folosit ca 'output'. Astfel, dupa ce am salvat intr-un vector ordinea in care se vor executa functiile ce desemneaza fiecare task, am implementat o structura de tip 'if' care va face acest lucru.

## Task 1
Dupa cum a fost cerut in cerinta, am folosit o lista simplu inlantuita in care am salvat echipele din fisier. Am lucrat cu o structura auxiliara de tip Team*(Team este o structura declarata in header in care salvez echipele) in care citeam fiecare detaliu din fisier. Tin sa mentionez ca unele denumiri de echipe aveau spatii la sfarsit, asa ca am tratat si acest caz. Dupa ce terminam de salvat toate datele necesare in auxiliar, il adaugam imediat la inceputul listei. La final, am afisat lista si am facut eliberarile de memorie necesare.

## Task 2
```shell
./checker.sh
````
