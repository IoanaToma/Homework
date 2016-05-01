//
//  main.cpp
//  Lab 4- Grafuri- Bellman Ford
//
//  Created by Ioana Toma on 23/04/14.
//  Copyright (c) 2014 Ioana Toma. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;

int nr_noduri, a[30][30];
int dist[30], pred[30], start;

void citire()
{
    ifstream f("/Users/Ioana/Desktop/XCode Projects/Lab 4- Grafuri- Bellman Ford/Lab 4- Grafuri- Bellman Ford/date.txt");
    
    f >> nr_noduri;
    for (int i=1; i<=nr_noduri; i++)
        for (int j=1; j<=nr_noduri; j++)
            f >> a[i][j];
    f.close();
}

void init()
{
    for (int i=1; i<=nr_noduri; i++)
    {
        if (i == start) dist[i] = 0;
        else dist[i] = 6000;
        pred[i] = -1;
    }
}

bool Bellman_Ford()
{
    init();
    for (int i=1; i<nr_noduri; i++)
        for (int j=1; j<=nr_noduri; j++)
            for (int k=1; k<=nr_noduri; k++)
                if (a[j][k])
                    if (dist[k] > dist[j] + a[j][k])
                    {
                        dist[k] = dist[j] + a[j][k];
                        pred[k] = j;
                    }
    for (int i=1; i<=nr_noduri; i++)
        for (int j=1; j<=nr_noduri; j++)
            if (dist[j] > dist[i] + a[i][j])
                return 0;
    return 1;
}

void afisare()
{
    cout << "Vectorul de distante este: " << endl;
    for (int i=1; i<=nr_noduri; i++)
        cout << dist[i] << " ";
    cout << endl << "Vectorul de predecesori este: " << endl;
    for (int i=1; i<=nr_noduri; i++)
        if (pred[i] != -1) cout << pred[i] << " ";
        else cout << "/ ";
}


int main()
{
    citire();
    cout << "Dati nodul de start: ";
    cin >> start;
    Bellman_Ford();
    afisare();
    
    return 0;
}

