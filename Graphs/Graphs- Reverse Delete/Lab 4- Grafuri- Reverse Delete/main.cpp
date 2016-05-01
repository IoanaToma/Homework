//
//  main.cpp
//  Lab 4- Grafuri- Reverse Delete
//
//  Created by Ioana Toma on 24/04/14.
//  Copyright (c) 2014 Ioana Toma. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;

struct muchie
{
    int a, b;
};

int a[30][30], nr_noduri, nr_muchii = 0;
int viz[30], n;
muchie mch[50];

void citire()
{
    ifstream f("/Users/Ioana/Desktop/XCode Projects/Lab 4- Grafuri- Kruskal/Lab 4- Grafuri- Kruskal/date.txt");
    
    f >> nr_noduri;
    for (int i=1; i<=nr_noduri; i++)
        for (int j=1; j<=nr_noduri; j++)
            f >> a[i][j];
    f.close();
}

void afisare()
{
    for (int i=1; i<=nr_noduri; i++)
    {
        for (int j=1; j<=nr_noduri; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
}

void DF (int x)
{
    viz[x] = 1;
    n++;
    
    int i;
    for (i=1; i<=nr_noduri; i++)
        if (a[x][i])
            if (!viz[i])
                DF (i);
}

void sort ()
{
    int i, j;
    for (i=2; i<=nr_noduri; i++)
        for (j=1; j<i; j++)
            if (a[i][j])
            {
                mch[nr_muchii].a = j;
                mch[nr_muchii++].b = i;
            }
    for (i=0; i<nr_muchii-1; i++)
        for (j=i+1; j<nr_muchii; j++)
            if (a[mch[i].a][mch[i].b] < a[mch[j].a][mch[j].b])
            {
                muchie t;
                t = mch[i];
                mch[i] = mch[j];
                mch[j] = t;
            }
}

void init()
{
    for (int i=1; i<=nr_noduri; i++)
        viz[i] = 0;
    n = 0;
}

void Reverse_Delete()
{
    sort();
    for (int i=0; i<nr_muchii; i++)
    {
        int x = mch[i].a, y = mch[i].b;
        int cost = a[x][y];
        a[x][y] = 0;
        a[y][x] = 0;
        init();
        DF(1);
        if (n != nr_noduri)
        {
            a[x][y] = cost;
            a[y][x] = cost;
        }
    }
}

int main()
{
    citire();
    cout << "Matricea initiala este: " << endl;
    afisare();
    cout << endl << "Matricea noua este: " << endl;
    sort();
    Reverse_Delete();
    afisare();
    
    return 0;
}

