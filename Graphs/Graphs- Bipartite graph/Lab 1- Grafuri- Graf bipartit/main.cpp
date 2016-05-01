//
//  main.cpp
//  Lab 1- Grafuri- Graf bipartit
//
//  Created by Ioana Toma on 28/02/14.
//  Copyright (c) 2014 Ioana Toma. All rights reserved.
//

#include <iostream>
#include <fstream>

int v[20];

int bipartit (int x, int a[20][20], int n)
{
    v[x] = 1;
    
    int j;
    for (j=1; j<=n; j++)
        if (a[x][j])
            v[j] = 2;
    
    int i;
    for (i=1; i<=n; i++)
        if (!v[i])
        {
            v[i] = 1;
            for (j=1; j<=n; j++)
                if (a[i][j])
                    v[j] = 2;
            
        }
    
    for (i=1; i<=n; i++)
        for (j=1; j<=n; j++)
            if (a[i][j] && (v[i] == v[j]))
                return 0;
    
    return 1;
}

using namespace std;

int main()
{
    ifstream f ("/Users/Ioana/Desktop/XCode Projects/Lab 1- Grafuri- Graf bipartit/Lab 1- Grafuri- Graf bipartit/Matrice.txt");
    
    int n, start, a[20][20], i, j;
    f >> n;
    f >> start;
    for (i=1; i<=n; i++)
        for (j=1; j<=n; j++)
            f >> a[i][j];
    
    if (bipartit (start, a, n)) cout << "Graful este bipartit";
        else cout << "Graful nu este bipartit";
    
    
    return 0;
}

