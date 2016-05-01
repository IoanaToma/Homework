//
//  main.cpp
//  Lab 2- Grafuri- Arbori + Centru + Diametru
//
//  Created by Ioana Toma on 30/03/14.
//  Copyright (c) 2014 Ioana Toma. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;

int viz[30], m = 0, maxim = 0, nod, f1, f2;

void DF (int x, int a[30][30], int n) //l-am folosit ca sa verific daca graful e arbore - daca nu are cicluri
{
    viz[x] = 1;
    m++; //imi va retine cate noduri au fost vizitate in parcurgere, iar apoi voi verifica daca au fost vizitate toate (daca e conex)
    
    int i, j = x+1;
    for (i=j; i<=n; i++)
        if (a[x][i])
        {
            if (!viz[i])
                DF (i, a, n);
            else return;
        }
}

void initializare_viz(int n) //initializarea vectorului viz cu 0 - faceam asta de mai multe ori
{
    int i;
    for (i=1; i<=n; i++)
        viz[i] = 0;
}

int lungime (int x, int a[30][30], int n, int distanta) //DF modificat astfel incat sa imi retina atat nodul la care se opreste, cat si distanta
{                                                       //va ajunge in jos pana la cea mai departata frunza de nodul x
    if (distanta > maxim)
    {
        maxim = distanta;
        nod = x;
    }
    viz[x] = 1;
    
    int i;
    for (i=1; i<=n; i++)
        if (a[x][i] && !viz[i])
            lungime (i, a, n, distanta + 1);
    
    return maxim;
}

int diametru (int a[30][30], int nr_noduri, int distanta)
{
    lungime (1, a, nr_noduri, distanta); //apelez o data pentru a retine in variabila "nod" cea mai departata frunza
    f1 = nod; //voi avea nevoie de f1 pentru centru
    initializare_viz(nr_noduri); //initializez din nou vectorul de vizitari
    return lungime (nod, a, nr_noduri, distanta); //apelez din nou lungime, plecand din frunza gasita; astfel, va ajunge la cea mai departata
}                                                 //frunza de ea si imi va returna distanta dintre ele, adica diametrul grafului

void centru (int a[30][30], int nr_noduri, int d)
{
    int predecesor[30], stiva[30], n = 0, k = f1, diam = d;
    initializare_viz(nr_noduri);
    int i;
    for (i=1; i<=nr_noduri; i++)
        predecesor[i] = 0; //initializez vectorul de predecesori cu 0
    stiva[n++] = k; //simulez o stiva cu un vector, fiindca vreau sa fac un fel de DF, dar nu recursiv; in stiva pun frunza1
    viz[k] = 1; //si o marchez ca fiind vizitata
    
    while (n) //cat timp mai am elemente in stiva
    {
        n--; //sterg ultimul element
        viz[k] = 1; //k va fi mereu ultimul element din stiva (inainte de stergere)
        for (i=1; i<=nr_noduri; i++)
            if (a[k][i] && !viz[i])
            {
                stiva[n++] = i; //pun in stiva toti vecinii lui k
                predecesor[i] = k; //daca i nu este nod vizitat, atunci clar predecesorul lui in drumul care da diametrul este k
            }
        
        if (n == 0) break;
        k = stiva[n-1];
        
        while (n && viz[k]) //sterg elementele vizitate din stiva
        {
            k = stiva[n-1];
            n--;
        }
    }
    
    int x = f2; //initial, x va fi frunza 2; acum refac drumul care da diametrul arborelui
    i = 0;
    while (x)
    {
        if (i == diam/2)
            cout << x;
        else if (diam%2 && i == diam/2+1) //daca diametrul e par, centrul e format dintr-un singur nod, cel de la mijloc; impar- 2 noduri
            cout << " " << x;
        x = predecesor[x]; //x va deveni predecesorul sau
        i++;
    }
}


int main()
{
    ifstream f("/Users/Ioana/Desktop/XCode Projects/Lab 2- Grafuri- Arbori + Centru + Diametru/Lab 2- Grafuri- Arbori + Centru + Diametru/date.txt");
    
    int nr_noduri, nr_muchii = 0, a[30][30], i, j;
    f >> nr_noduri;
    for(i=1; i<=nr_noduri; i++)
        for(j=1; j<=nr_noduri; j++)
        {
            f >> a[i][j];
            if (a[i][j] && j > i) nr_muchii++; //numar cate muchii are graful
        }
    if (nr_muchii != nr_noduri - 1) //daca nu are exact n-1 muchii, nu este arbore
        cout << "Graful nu este un arbore!" << endl;
    else //daca totusi are, trebuie sa verific daca e conex si nu are cicluri
    {
        DF (1, a, nr_noduri);
        if (m != nr_noduri) //inseamna ca ori s-a oprit parcurgerea ca a gast un ciclu, ori graful nu e conex
            cout << "Graful nu este un arbore!" << endl;
        else
        {
            cout << "Graful este un arbore!" << endl;
            
            initializare_viz(nr_noduri);
            int distanta = 0;
            cout << "Diametrul arborelui este: ";
            int diam = diametru (a, nr_noduri, distanta);
            cout << diam << endl;
            f2 = nod;
            
            cout << "Centrul arborelui este format din nodurile: ";
            centru (a, nr_noduri, diam);
            cout << endl;
        }
    }
    
    f.close();

    return 0;
}

