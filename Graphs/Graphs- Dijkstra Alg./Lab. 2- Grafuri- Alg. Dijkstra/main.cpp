//
//  main.cpp
//  Lab. 2- Grafuri- Alg. Dijkstra
//
//  Created by Ioana Toma on 29/03/14.
//  Copyright (c) 2014 Ioana Toma. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;

int viz[30], tata[30], distanta[30], infinit = 60000;

void Dijkstra (int nod_start, int a[30][30], int nr_noduri)
{
    int i;
    for (i=1; i<=nr_noduri; i++)
    {
        viz[i] = 0;
        tata[i] = nod_start;
        if (a[nod_start][i]) distanta[i] = a[nod_start][i];
        else distanta[i] = infinit;
    }
    viz[nod_start] = 1;
    distanta[nod_start] = -1;
    
    int min, nod, ok = 0;
    while (!ok)
    {
        min = infinit; //gasesc distanta minima si memorez nodul
        for (i=1; i<=nr_noduri; i++)
            if (!viz[i] && distanta[i] <= min)
            {
                nod = i;
                min = distanta[i];
            }
        viz[nod] = 1; //marchez nodul respectiv ca fiind vizitat
        int k;
        for (i=1; i<=nr_noduri; i++) //pentru celelalte noduri, verific daca drumul care trece prin nodul nou gasit este mai scurt
            if (!viz[i])
            {
                if (a[nod][i]) k = a[nod][i];
                else k = infinit;
                if (distanta[i] > distanta[nod] + k)
                {
                    distanta[i] = distanta[nod] + k;
                    tata[i] = nod;
                }
            }
        ok = 1; //verific daca mai am noduri nevizitate
        for (i=1; i<=nr_noduri; i++)
            if (!viz[i]) ok = 0;
    }
}

int main()
{
    ifstream f("/Users/Ioana/Desktop/XCode Projects/Lab. 2- Grafuri- Alg. Dijkstra/Lab. 2- Grafuri- Alg. Dijkstra/date.txt");
    
    int nr_noduri, a[30][30], i, j;
    f >> nr_noduri;
    for (i=1; i<=nr_noduri; i++)
        for (j=1; j<=nr_noduri; j++)
            f >> a[i][j];
    for (i=1; i<=nr_noduri; i++)
    {
        for (j=1; j<=nr_noduri; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
    
    int nod_start;
    cout << "Dati nodul de start: ";
    cin >> nod_start;
    
    Dijkstra(nod_start, a, nr_noduri);

//afisarea vectorului cu distantele minime de la nodul de start la toate celelalte
    for (i=1; i<=nr_noduri; i++)
    {
        if (distanta[i] == infinit) tata[i] = -1;
        cout << distanta[i] << " ";
    }
    cout << endl << endl;
    
//reconstituirea drumului de la nodul de start la un nod citit de la tastatura
    int nod1, nod2;
    cout << "Dati nodul pana la care doriti sa aflati drumul minim: ";
    cin >> nod1;
    if (nod1 > nr_noduri)
        cout << "Nodul dat nu exista in graf!";
    else
        if (distanta[nod1] == infinit)
            cout << "Nu exista drum de la nodul de start la nodul dat!";
        else
        {
            nod2 = tata[nod1];
            long m = nod2;
            while (nod2 != nod_start)
            {
                nod2 = tata[nod2];
                m = m * 10 + nod2;
            }
            while (m)
            {
                cout << m%10 << " ";
                m = m/10;
            }
            cout << nod1;
        }
    cout << endl;
    
    
    f.close();

    return 0;
}

