//
//  main.cpp
//  Lab 5- Grafuri- Hungarian Algorithm
//
//  Created by Ioana Toma on 04/05/14.
//  Copyright (c) 2014 Ioana Toma. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;

class Graph
{
    int a[30][30];
    int nr_noduri;
    int matrix[30][30];
    
public:
    Graph();
    void citire();
    void Step0();
    void Step1();
    void Step2();
    void Hungarian_Algorithm();
};

Graph::Graph()
{
    nr_noduri = 0;
    for (int i=1; i<=nr_noduri; i++)
        for (int j=1; j<=nr_noduri; j++)
        {
            a[i][j] = 0;
            matrix[i][j] = 0;
        }
}

void Graph::citire()
{
    ifstream f("/Users/Ioana/Desktop/XCode Projects/Lab 5- Grafuri- Hungarian Algorithm/Lab 5- Grafuri- Hungarian Algorithm/date.txt");
    
    f >> nr_noduri;
    for (int i=1; i<=nr_noduri; i++)
        for (int j=1; j<=nr_noduri; j++)
        {
            f >> a[i][j];
            matrix[i][j] = a[i][j];
        }
    f.close();
}

void Graph::Step0()
{
    for (int i=1; i<=nr_noduri; i++)
    {
        int min = matrix[i][1];
        for (int j=2; j<=nr_noduri; j++)
            if (matrix[i][j] < min) min = matrix[i][j];
        for (int j=1; j<=nr_noduri; j++)
            matrix[i][j] = matrix[i][j] - min;
    }
    for (int i=1; i<=nr_noduri; i++)
    {
        int min = matrix[1][i];
        for (int j=2; j<=nr_noduri; j++)
            if (matrix[j][i] < min) min = matrix[j][i];
        if(min)
            for (int j=1; j<=nr_noduri; j++)
                matrix[j][i] = matrix[j][i] - min;
    }
}

void Graph::Step1()
{
    int cup[30][30];
    int max, linie, coloana, cuplaj = 0;
    char ok = 'b';
    
    while (cuplaj < nr_noduri)
    {
        for (int i=1; i<=nr_noduri; i++)
            for (int j=1; j<=nr_noduri; j++)
                cup[i][j] = 0;
        cuplaj = 0;
        ok = 'b';
        
        while (ok != 'a')
        {
            ok = 'a';
            max = 0; linie = -1; coloana = -1;
            for (int i=1; i<=nr_noduri; i++)
            {
                int counter = 0;
                for (int j=1; j<=nr_noduri; j++)
                    if (!matrix[i][j]) counter++;
                if (counter > max)
                {
                    ok = 'l';
                    linie = i;
                    max = counter;
                }
            }
            for (int j=1; j<=nr_noduri; j++)
            {
                int counter = 0;
                for (int i=1; i<=nr_noduri; i++)
                    if (!matrix[i][j]) counter++;
                if (counter > max)
                {
                    ok = 'c';
                    coloana = j;
                    max = counter;
                }
            }
            if (ok == 'l')
            {
                for (int i=1; i<=nr_noduri; i++)
                    cup[linie][i]--;
                for (int i=1; i<=nr_noduri; i++)
                    if (!matrix[linie][i])
                        matrix[linie][i] = -1;
                cuplaj++;
            }
            if (ok == 'c')
            {
                for (int i=1; i<=nr_noduri; i++)
                    cup[i][coloana]--;
                for (int i=1; i<=nr_noduri; i++)
                    if (!matrix[i][coloana])
                        matrix[i][coloana] = -1;
                cuplaj++;
            }
        }
        if (cuplaj < nr_noduri)
        {
            int min = 1000;
            for (int i=1; i<=nr_noduri; i++)
                for (int j=1; j<=nr_noduri; j++)
                    if (matrix[i][j] < min && matrix[i][j] != -1 && !cup[i][j])
                        min = matrix[i][j];
            
            for (int i=1; i<=nr_noduri; i++)
                for (int j=1; j<=nr_noduri; j++)
                    if (matrix[i][j] == -1) matrix[i][j] = 0;
            
            for (int i=1; i<=nr_noduri; i++)
                for (int j=1; j<=nr_noduri; j++)
                {
                    if (!cup[i][j])
                        matrix[i][j] = matrix[i][j] - min;
                    if (cup[i][j] == -2)
                        matrix[i][j] = matrix[i][j] + min;
                }
        }
        else
            for (int i=1; i<=nr_noduri; i++)
                for (int j=1; j<=nr_noduri; j++)
                    if (matrix[i][j] == -1) matrix[i][j] = 0;
    }
}

void Graph::Step2()
{
    int min, counter, linie = -1, coloana = -1, acoperire = 0, cost = 0;
    
    while (acoperire < nr_noduri)
    {
        min = 1000;
        for (int i=1; i<=nr_noduri; i++)
        {
            counter = 0;
            for (int j=1; j<=nr_noduri; j++)
                if (!matrix[i][j]) counter++;
            if (counter < min && counter)
            {
                min = counter;
                linie = i;
            }
        }
        for (int j=1; j<=nr_noduri; j++)
            if (!matrix[linie][j]) coloana = j;
        for (int i=1; i<=nr_noduri; i++)
            if (!matrix[i][coloana]) matrix[i][coloana] = -1;
        for (int i=1; i<=nr_noduri; i++)
            if (!matrix[linie][i]) matrix[linie][i] = -1;
        
        cout << "Muncitorul " << linie << " primeste slujba " << coloana << endl;
        cost = cost + a[linie][coloana];
        acoperire++;
    }
    cout << "Costul este: " << cost << endl << endl;
}

void Graph::Hungarian_Algorithm()
{
    citire();
    Step0();
    Step1();
    Step2();
}

int main()
{
    Graph G;
    G.Hungarian_Algorithm();
    return 0;
}

