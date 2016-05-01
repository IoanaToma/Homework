//
//  main.cpp
//  Lab 4- Grafuri- Neville
//
//  Created by Ioana Toma on 26/04/14.
//  Copyright (c) 2014 Ioana Toma. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;

class Tree
{
    int a[30][30];
    int nr_noduri;
    int cod[30], n_cod;

public:
    Tree();
    void citire();
    void Codificare_Neville();
    void afisare_cod();
    void Decodificare_Neville();
    void afisare_matrice();
};

Tree::Tree()
{
    n_cod = 0;
    nr_noduri = 0;
}

void Tree::citire()
{
    ifstream f("/Users/Ioana/Desktop/XCode Projects/Lab 4- Grafuri- Neville/Lab 4- Grafuri- Neville/date.txt");
    
    f >> nr_noduri;
    for (int i=1; i<=nr_noduri; i++)
        for (int j=1; j<=nr_noduri; j++)
            f >> a[i][j];
    f.close();
}

void Tree::Codificare_Neville()
{
    while (n_cod < nr_noduri-2)
    {
        int ok = 1, nr = 0;
        for (int i=1; i<=nr_noduri && ok; i++)
        {
            int grad = 0, adiacent = -1;
            for (int j=1; j<=nr_noduri; j++)
                if (a[i][j] && a[i][j] != -1)
                {
                    grad++;
                    adiacent = j;
                }
            if (grad == 1)
            {
                nr++;
                cod[n_cod++] = adiacent;
                a[i][i] = -1;
            }
            if (n_cod == nr_noduri -2) ok = 0;
        }
        for (int i=1; i<=nr_noduri && nr; i++)
        {
            int grad = 0, adiacent = -1, j;
            for (j=1; j<=nr_noduri; j++)
                if (a[i][j] && a[i][j] != -1)
                {
                    grad++;
                    adiacent = j;
                }
            if (grad == 1)
            {
                a[i][adiacent] = 0;
                a[adiacent][i] = 0;
                nr--;
            }
        }
    }
    for (int i=1; i<=nr_noduri; i++)
        if (a[i][i] != -1)
            for (int j=1; j<=nr_noduri; j++)
                if (a[i][j] == 1)
                {
                    cod[n_cod++] = j;
                    a[i][j] = 0;
                    a[i][i] = -1;
                }
}

void Tree::afisare_cod()
{
    for (int i=0; i<n_cod; i++)
        cout << cod[i] << " ";
    cout << endl << endl;
}

void Tree::Decodificare_Neville()
{
    int varfuri[30];
    for (int i=1; i<=nr_noduri; i++)
        varfuri[i] = i;
    
    for (int i=1; i<=nr_noduri; i++)
        a[i][i] = 0;
    
    int nr = 0, poz = 0;
    while (nr < nr_noduri - 2)
    {
        int aux[30], nr_aux = 0, ok = 1;
        for (int i=1; i<=nr_noduri && ok; i++)
            if (varfuri[i])
            {
                int ok1 = 1;
                for (int j=0; j<n_cod; j++)
                    if (cod[j] == varfuri[i] && cod[j]) ok1 = 0;
                if (ok1)
                {
                    aux[nr_aux++] = varfuri[i];
                    nr++;
                }
                if (nr == nr_noduri - 2) ok = 0;
            }
        for (int i=0; i<nr_aux; i++)
        {
            a[aux[i]][cod[poz]] = 1;
            a[cod[poz]][aux[i]] = 1;
            cod[poz] = 0;
            poz++;
            varfuri[aux[i]] = 0;
        }
    }
    int first = 0, second = 0;
    for (int i=1; i<=nr_noduri; i++)
        if (varfuri[i])
        {
            if (!first) first = varfuri[i];
            else second = varfuri[i];
        }
    a[first][second] = 1;
    a[second][first] = 1;
}

void Tree::afisare_matrice()
{
    for (int i=1; i<=nr_noduri; i++)
    {
        for (int j=1; j<=nr_noduri; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
}

int main()
{
    Tree T;
    T.citire();
    T.Codificare_Neville();
    T.afisare_cod();
    T.Decodificare_Neville();
    T.afisare_matrice();
    
    return 0;
}


