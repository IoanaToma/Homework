//
//  main.cpp
//  Lab 2- Grafuri- Alg. Prim
//
//  Created by Ioana Toma on 20/03/14.
//  Copyright (c) 2014 Ioana Toma. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream f ("/Users/Ioana/Desktop/XCode Projects/Lab 2- Grafuri- Alg. Prim/Lab 2- Grafuri- Alg. Prim/date.txt");
    
    int n, a[20][20], i, j;
    f >> n;
    for (i=1; i<=n; i++)
        for (j=1; j<=n; j++)
            f >> a[i][j];
    for (i=1; i<=n; i++)
    {
        for (j=1; j<=n; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
    
    int viz[20];
    for (i=1; i<=n; i++)
        viz[i] = 0;
    
    int nod_inc, nod = -1;
    cout << "Dati nodul de inceput:";
    cin >> nod_inc;
    viz[nod_inc] = 1;
    cout << nod_inc << " ";
    
    int min = 1000;
    for (j=1; j<=n; j++)
        if (a[nod_inc][j] < min && a[nod_inc][j])
        {
            min = a[nod_inc][j];
            nod = j;
        }
    viz[nod] = 1;
    cout << nod << " " << endl;
    
    int ok = 1, nod1 = -1, nod2 = -1;
    while (ok)
    {
        min = 1000;
        for (i=1; i<=n; i++)
            if (viz[i])
            {
                for (j=1; j<=n; j++)
                    if (a[i][j] && a[i][j] < min)
                        if (!viz[j])
                        {
                            min = a[i][j];
                            nod1 = i;
                            nod2 = j;
                        }
            }
        viz[nod2] = 1;
        cout << nod1 << " " << nod2 << endl;
        
        ok = 0;
        for (i=1; i<=n; i++)
            if (!viz[i]) ok = 1;
    }

    
    f.close();
    
    return 0;
}

