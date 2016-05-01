//
//  main.cpp
//  Lab 2- Grafuri- Centru graf conex
//
//  Created by Ioana Toma on 31/03/14.
//  Copyright (c) 2014 Ioana Toma. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;

int viz[30], distanta[30], infinit = 60000;

void Dijkstra (int x, int a[30][30], int n)
{
    int i;
    for (i=1; i<=n; i++)
    {
        viz[i] = 0;
        if (a[x][i]) distanta[i] = a[x][i];
        else distanta[i] = infinit;
    }
    viz[x] = 1;
    distanta[x] = -1;
    
    int min, nod = 0, ok = 0;
    while (!ok)
    {
        min = infinit; //gasesc distanta minima si memorez nodul
        for (i=1; i<=n; i++)
            if (!viz[i] && distanta[i] <= min)
            {
                nod = i;
                min = distanta[i];
            }
        viz[nod] = 1; //marchez nodul respectiv ca fiind vizitat
        int k;
        for (i=1; i<=n; i++) //pentru celelalte noduri, verific daca drumul care trece prin nodul nou gasit este mai scurt
            if (!viz[i])
            {
                if (a[nod][i]) k = a[nod][i];
                else k = infinit;
                if (distanta[i] > distanta[nod] + k)
                    distanta[i] = distanta[nod] + k;
            }
        ok = 1; //verific daca mai am noduri nevizitate
        for (i=1; i<=n; i++)
            if (!viz[i]) ok = 0;
    }
}

int main()
{
    ifstream f ("/Users/Ioana/Desktop/XCode Projects/Lab 2- Grafuri- Centru graf conex/Lab 2- Grafuri- Centru graf conex/date.txt");
    
    int nr_noduri, a[30][30], i, j;
    f >> nr_noduri;
    for (i=1; i<=nr_noduri; i++)
        for (j=1; j<=nr_noduri; j++)
            f >> a[i][j];
    
    int exc[30], e;
    for (i=1; i<=nr_noduri; i++)
    {
        Dijkstra(i, a, nr_noduri);
        e = 0;
        for (j=1; j<=nr_noduri; j++)
            if (distanta[j] > e) e = distanta[j];
        exc[i] = e;
    }
    int minim = infinit;
    for (i=1; i<=nr_noduri; i++)
        if (exc[i] < minim) minim = exc[i];
    cout << "Raza grafului este: " << minim << endl;
    cout << "Centrul grafului este format din varfurile: ";
    for (i=1; i<=nr_noduri; i++)
        if (exc[i] == minim) cout << i << " ";
    cout << endl;
    
    f.close();
    
    return 0;
}

