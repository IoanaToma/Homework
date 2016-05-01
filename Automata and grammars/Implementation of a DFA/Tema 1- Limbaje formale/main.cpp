//
//  main.cpp
//  Tema 1- Limbaje formale
//
//  Created by Ioana Toma on 05/03/14.
//  Copyright (c) 2014 Ioana Toma. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main()
{
    ifstream f("/Users/Ioana/Desktop/XCode Projects/Tema 1- Limbaje formale/Tema 1- Limbaje formale/date.txt");
    
    int st_in, st_fin[10], n_fin, nr_stari;
    f >> nr_stari >> st_in >> n_fin; // citeste nr de stari, starea initiala, nr de stari finale
    int i;
    for (i = 0; i<n_fin; i++) //citeste starile finale
        f >> st_fin[i];
    
    char alfabet[20];
    int n_alfabet;
    f >> n_alfabet; //citeste numarul de litere ale alfabetului
    for (i=0; i<n_alfabet; i++) //citeste alfabetul
        f >> alfabet[i];
    cout << "Alfabetul este: ";
    for (i=0; i<n_alfabet; i++) //afiseaza alfabetul
        cout << alfabet[i];
    cout << endl;
    
    int a[20][20]; //a = matricea de tranzitii
    int j, k = 1, x;
    int nr_tranzitii;
    f >> nr_tranzitii; //citeste nr de tranzitii
    for (i=0; i<nr_stari; i++)
        for (j=0; j<n_alfabet; j++)
            a[i][j] = -1; //initializeaza matricea de tranzitii cu -1
    while (k <= nr_tranzitii) //citeste tranzitiile din fisier (de unde pleaca, cu ce, unde ajunge)
    {
        f >> i >> x >> j;
        a[i][x] = j; //x = cu ce se face tranzitia de la i la j; x = pozitia caracterului in alfabet
        k++;
    }
//Afisarea matricei de tranzitii
    cout << "Matricea de tranzitii este: " << endl;
    for (i=0; i<nr_stari; i++)
    {
        for (j=0; j<n_alfabet; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
    
    char cuvant[30];
    int l_cuvant;
    f >> l_cuvant; //citeste lungimea cuvantului
    for (i=0; i<l_cuvant; i++) //citeste literele cuvantului
        f >> cuvant[i];
    cout << "Cuvantul este: ";
    for (i=0; i<l_cuvant; i++)
        cout << cuvant[i];
    cout << endl;
    
    i = st_in;
    for (j=0; j<l_cuvant; j++)
    {
        int ok = 0;
        k = 0;
        while (!ok && k<n_alfabet) //verifica daca caracterul este in alfabet
        {
            if (cuvant[j] == alfabet[k])
                ok = 1;
            k++;
        }
        if (!ok) //daca nu e in alfabet, iese
        {
            cout << "Cuvantul nu este recunoscut de automat!";
            break;
        }
        else //altfel k = pozitia pe care se gaseste caracterul in alfabet
        {
            k--;
            i = a[i][k]; //i devine starea in care ajunge cu caracterul citit din cuvant
            if (i == -1) //daca nu ajunge in nicio stare cu caracterul respectiv, iese
            {
                cout << "Cuvantul nu este recunoscut de automat!";
                break;
            }
            else //daca ajunge, verifica si daca cumva este la sfarsitul cuvantului si ar trebui sa ajunga in st finala
            {
                if (j == l_cuvant - 1)
                {
                    int ok2 = 0;
                    k = 0;
                    while (!ok2 && k<n_fin)
                    {
                        if (i == st_fin[k]) ok2 = 1;
                        k++;
                    }
                    if (!ok2) cout << "Cuvantul nu este recunoscut de automat!";
                    else cout << "Cuvantul este recunoscut de automat!";
                }
            }
        }
    }

    f.close();

    return 0;
}

