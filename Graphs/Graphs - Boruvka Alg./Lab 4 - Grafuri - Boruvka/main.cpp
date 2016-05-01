//
//  main.cpp
//  Lab 4 - Grafuri - Boruvka
//
//  Created by Ioana Toma on 03/04/14.
//  Copyright (c) 2014 Ioana Toma. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;

struct muchie
{
    int a, b;
};

muchie m[50];
int b[30][30], viz[30], noduri;
int nr_noduri, a[30][30];

void DF (int x, int a[30][30], int n)
{
    viz[x] = 1;
    noduri++;
    
    int i;
    for (i=1; i<=n; i++)
        if (a[x][i] && !viz[i])
            DF (i, a, n);
}

void citire()
{
    ifstream f("/Users/Ioana/Desktop/XCode Projects/Lab 4 - Grafuri - Boruvka/Lab 4 - Grafuri - Boruvka/date.txt");
    
    f >> nr_noduri;
    for (int i=1; i<=nr_noduri; i++)
        for (int j=1; j<=nr_noduri; j++)
            f >> a[i][j];
    f.close();
}

void Boruvka()
{
    int k = 0, nod = -1, minim, ok = 1;
    
    for (int i=1; i<=nr_noduri; i++)
    {
        minim = 1000;
        for (int j=1; j<=nr_noduri; j++)
            if (a[i][j] < minim && a[i][j])
            {
                minim = a[i][j];
                nod = j;
            }
        if (!b[i][nod])
        {
            m[k].a = i;
            m[k].b = nod;
            k++;
            
            b[i][nod] = 1;
            b[nod][i] = 1;
        }
    }
    DF(1, b, nr_noduri); //fac parcurgerea
    if (noduri != nr_noduri) //vad daca graful partial obtinut e conex sau nu; daca nu e, continuam algoritmul
        ok = 0;
    
    while (!ok)
    {
        int nod1 = -1;
        int i = 1;
        minim = 1000;
        while (i<=nr_noduri)
        {
            for (int j=1; j<=nr_noduri; j++)
                if (a[i][j])
                    if (a[i][j] < minim && !b[i][j])
                    {
                        minim = a[i][j];
                        nod = j;
                        nod1 = i;
                    }
            i++;
        }
        m[k].a = nod1;
        m[k].b = nod;
        k++;
        
        b[nod1][nod] = 1;
        b[nod][nod1] = 1;
        
        ok = 1;
        for (int x=1; x<=nr_noduri; x++) //initializez de fiecare data vectorul de vizitari cu 0
            viz[x] = 0;
        noduri = 0;
        DF(1, b, nr_noduri); //fac parcurgerea
        if (noduri != nr_noduri) //vad daca graful partial obtinut e conex sau nu; daca nu e, continuam algoritmul
            ok = 0;
    }
    
    for (int i=0; i<k; i++)
        cout << m[i].a << " " << m[i].b << endl;
}


int main()
{
    citire();
    Boruvka();
    
    return 0;
}

