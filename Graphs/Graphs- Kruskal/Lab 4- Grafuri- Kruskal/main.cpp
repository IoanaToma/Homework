//
//  main.cpp
//  Lab 4- Grafuri- Kruskal
//
//  Created by Ioana Toma on 23/04/14.
//  Copyright (c) 2014 Ioana Toma. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;

struct muchie
{
    int a, b;
};

int viz1[30], a[30][30], b[30][30], nr_muchii, nr_noduri;
muchie mch[100];

void citire ()
{
    ifstream f("/Users/Ioana/Desktop/XCode Projects/Lab 4- Grafuri- Kruskal/Lab 4- Grafuri- Kruskal/date.txt");

    f >> nr_noduri;
    for (int i=1; i<=nr_noduri; i++)
        for (int j=1; j<=nr_noduri; j++)
            f >> a[i][j];
    f.close();
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
            if (a[mch[i].a][mch[i].b] > a[mch[j].a][mch[j].b])
            {
                muchie t;
                t = mch[i];
                mch[i] = mch[j];
                mch[j] = t;
            }
}

void Kruskal()
{
    int conex[30];
    for (int i=1; i<=nr_noduri; i++)
        conex[i] = i;
    
    sort ();
    b[mch[0].a][mch[0].b] = 1;
    b[mch[0].b][mch[0].a] = 1;
    viz1[mch[0].a] = 1;
    viz1[mch[0].b] = 1;
    conex[mch[0].b] = mch[0].a;
    cout << mch[0].a << " " << mch[0].b << endl;
    
    int numar = 1, k = 1, adaug = 2, oka, okb;
    while (numar < nr_noduri-1)
        if (viz1[mch[k].a] && viz1[mch[k].b] && conex[mch[k].a] == conex[mch[k].b])
            k++;
        else
        {
            oka = okb = 0;
            
            b[mch[k].a][mch[k].b] = 1;
            b[mch[k].b][mch[k].a] = 1;
            numar++;
            if (!viz1[mch[k].a])
            {
                adaug++;
                oka = 1;
                viz1[mch[k].a] = 1;
            }
            if (!viz1[mch[k].b])
            {
                adaug++;
                okb = 1;
                viz1[mch[k].b] = 1;
            }
            int x = mch[k].a, y = mch[k].b, c = conex[x];
            for (int i=1; i<=nr_noduri; i++)
                if (conex[i] == c)
                    conex[i] = conex[y];
            cout << mch[k].a << " " << mch[k].b << endl;
            k++;
        }
}

int main()
{
    citire();
    Kruskal();
    
    return 0;
}

