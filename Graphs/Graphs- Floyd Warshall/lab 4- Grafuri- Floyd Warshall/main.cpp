//
//  main.cpp
//  lab 4- Grafuri- Floyd Warshall
//
//  Created by Ioana Toma on 23/04/14.
//  Copyright (c) 2014 Ioana Toma. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;

int nr_noduri, a[30][30];
int matrice [30][30];

void citire()
{
    ifstream f("/Users/Ioana/Desktop/XCode Projects/lab 4- Grafuri- Floyd Warshall/lab 4- Grafuri- Floyd Warshall/date.txt");
    
    f >> nr_noduri;
    for (int i=1; i<=nr_noduri; i++)
        for (int j=1; j<=nr_noduri; j++)
            f >> a[i][j];
    f.close();
}

void afisare ()
{
    for (int i=1; i<=nr_noduri; i++)
    {
        for (int j=1; j<=nr_noduri; j++)
            if (matrice[i][j] == 6000) cout << "INF ";
            else cout << matrice[i][j] << " ";
        cout << endl;
    }
}

void Floyd_Warshall ()
{
    for (int i=1; i<=nr_noduri; i++)
        for (int j=1; j<=nr_noduri; j++)
            matrice[i][j] = a[i][j];
    for (int k=1; k<=nr_noduri; k++)
        for (int i=1; i<=nr_noduri; i++)
            for (int j=1; j<=nr_noduri; j++)
                if (matrice[i][j] > matrice[i][k] + matrice[k][j])
                    matrice[i][j] = matrice[i][k] + matrice[k][j];
}

int main()
{
    citire();
    Floyd_Warshall();
    afisare();
    
    return 0;
}

