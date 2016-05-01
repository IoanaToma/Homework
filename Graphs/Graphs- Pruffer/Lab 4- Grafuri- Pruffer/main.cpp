//
//  main.cpp
//  Lab 4- Grafuri- Pruffer
//
//  Created by Ioana Toma on 27/04/14.
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
    void afisare_cod();
    void Codificare_Pruffer();
};

Tree::Tree()
{
    n_cod = 0;
    nr_noduri = 0;
}

void Tree::citire()
{
    ifstream f("/Users/Ioana/Desktop/XCode Projects/Lab 4- Grafuri- Pruffer/Lab 4- Grafuri- Pruffer/date.txt");
    
    f >> nr_noduri;
    for (int i=1; i<=nr_noduri; i++)
        for (int j=1; j<=nr_noduri; j++)
            f >> a[i][j];
    f.close();
}

void Tree::afisare_cod()
{
    for (int i=0; i<n_cod; i++)
        cout << cod[i] << " ";
    cout << endl << endl;
}

void Tree::Codificare_Pruffer()
{
    while (n_cod < nr_noduri-2)
    {
        int ok = 1;
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
                cod[n_cod++] = adiacent;
                a[i][adiacent] = 0;
                a[adiacent][i] = 0;
            }
            if (n_cod == nr_noduri -2) ok = 0;
        }
    }
}

int main()
{
    Tree T;
    T.citire();
    T.Codificare_Pruffer();
    T.afisare_cod();
    
    return 0;
}

