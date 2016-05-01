//
//  main.cpp
//  Lab 1- Grafuri- BF
//
//  Created by Ioana Toma on 27/02/14.
//  Copyright (c) 2014 Ioana Toma. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;

int viz[20];

struct nod
{
    int info;
    nod *urm;
};

void push (nod *&p, int x)
{
    if (p)
    {
        nod *q;
        q = new nod;
        q->info = x;
        q->urm = NULL;
        p->urm = q;
        p = q;
    }
    else
    {
        p = new nod;
        p->info = x;
        p->urm = NULL;
    }
    
}

void pop (nod *&coada)
{
    nod *q;
    q = coada;
    coada = coada->urm;
    delete q;
}

void BF (int x, nod *&coada, int a[20][20], int n)
{
    nod *p;
    push (coada, x);
    viz [x] = 1;
    p = coada;
    
    int i, j;
    while (coada)
    {
        i = coada->info;
        cout << i << " ";
        for (j = 1; j<=n; j++)
            if (a[i][j] && !viz[j])
            {
                push (p, j);
                viz[j] = 1;
            }
        pop (coada);
    }
}

int main()
{
    ifstream f ("/Users/Ioana/Desktop/XCode Projects/Lab 1- Grafuri- BF/Lab 1- Grafuri- BF/date.txt");
    
    int n, start, a[20][20], i, j;
    f >> n;
    f >> start;
    for (i=1; i<=n; i++)
        for (j=1; j<=n; j++)
            f >> a[i][j];
    
    nod *coada;
    
    BF (start, coada, a, n);
    
    for (i=1; i<=n; i++)
        if (!viz[i])
            BF (i, coada, a, n);
    
    f.close();
    
    return 0;
}


