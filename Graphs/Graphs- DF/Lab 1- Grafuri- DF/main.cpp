//
//  main.cpp
//  Lab 1- Grafuri- DF
//
//  Created by Ioana Toma on 28/02/14.
//  Copyright (c) 2014 Ioana Toma. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;

int viz [20];

void DF (int x, int a[20][20], int n)
{
    cout << x << " ";
    viz[x] = 1;
    
    int i;
    for (i=1; i<=n; i++)
        if (a[x][i] && !viz[i])
            DF (i, a, n);
}

using namespace std;

int main()
{
    ifstream f ("/Users/Ioana/Desktop/XCode Projects/Lab 1- Grafuri- BF/Lab 1- Grafuri- BF/date.txt");
    
    int n, start, a[20][20], i, j;
    f >> n;
    f >> start;
    for (i=1; i<=n; i++)
        for (j=1; j<=n; j++)
            f >> a[i][j];
    
    DF (start, a, n);
    
    for (i = 1; i<=n; i++)
        if (!viz[i])
            DF (i, a, n);
    
    f.close();
    
    return 0;
}

