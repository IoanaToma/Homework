//
//  main.cpp
//  Lab 2- Grafuri- Multiset grafic
//
//  Created by Ioana Toma on 06/03/14.
//  Copyright (c) 2014 Ioana Toma. All rights reserved.
//

#include <iostream>

using namespace std;

struct vector
{
    int val;
    int poz;
};

int matrice[30][30];

int main()
{
    int v[30], i, n;
    cout << "Dati numarul de noduri ale grafului: ";
    cin >> n;
    
    int n_m = n, n1 = n;
    
    cout << "Dati gradele nodurilor: ";
    for (i=0; i<n; i++)
        cin >> v[i];
/* Afisarea vectorului de grade
    cout << "Vectorul este: " << endl;
    for (i=0; i<n; i++)
        cout << v[i] << " ";
    cout << endl;*/
    
    vector a[30];
    for (i=0; i<n; i++)
    {
        a[i].val = v[i];
        a[i].poz = i+1;
    }
/* Afisarea vectorului structura
    for (i=0; i<n; i++)
    {
        cout << a[i].poz << " " << a[i].val;
        cout << endl;
    }*/
    
    int k = 1, s = 0;
    for (i=0; i<n; i++)
    {
        if (v[i] > n-1) k = 0;
        s = s + v[i];
    }
    if (!k || s%2) cout << "Nu e bine!";
    else
    {
        int ok = 1;
        while (n > 0 && ok)
        {
            int j, aux;
            for (i=0; i<n-1; i++)
                for (j=i+1; j<n; j++)
                    if(v[i] < v[j])
                    {
                        aux = v[i];
                        v[i] = v[j];
                        v[j] = aux;
                    }
            int x = v[0];
            for (j=0; j<n-1; j++)
                v[j] = v[j+1];
            n--;
            for (j=0; j<x; j++)
            {
                v[j]--;
                if (v[j] < 0)
                    ok = 0;
            }
        }
        if (!ok) cout << "Nu e bine!";
        else
        {
            int ok1 = 1;
            for (i=0; i<n; i++)
                if (v[i]) ok1 = 0;
            if (!ok1) cout << "Nu e bine!";
            else
            {
                cout << "E bine!" << endl;
                cout << "Matricea de adiacenta este: " << endl;
                while (n_m > 0)
                {
                    int j;
                    vector aux;
                    for (i=0; i<n_m-1; i++)
                        for (j=i+1; j<n_m; j++)
                            if(a[i].val < a[j].val)
                            {
                                aux = a[i];
                                a[i] = a[j];
                                a[j] = aux;
                            }
                    /*for (i=0; i<n_m; i++)
                     {
                     cout << a[i].poz << " " << a[i].val;
                     cout << endl;
                     }
                     cout << endl;*/
                    vector x;
                    x = a[0];
                    for (j=0; j<n_m; j++)
                        a[j] = a[j+1];
                    n_m--;
                    for (j=0; j<x.val; j++)
                    {
                        a[j].val--;
                        matrice[x.poz][a[j].poz] = 1;
                        matrice[a[j].poz][x.poz] = 1;
                    }
                }
                for (i=1; i<=n1; i++)
                {
                    int j;
                    for (j=1; j<=n1; j++)
                        cout << matrice[i][j] << " ";
                    cout << endl;
                }
            }
        }
    }
        
        
    
    return 0;
}

