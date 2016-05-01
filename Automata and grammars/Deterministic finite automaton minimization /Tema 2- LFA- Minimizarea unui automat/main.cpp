//
//  main.cpp
//  Tema 2- LFA- Minimizarea unui automat
//
//  Created by Ioana Toma on 01/04/14.
//  Copyright (c) 2014 Ioana Toma. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;

bool apartine(int st_fin[30], int x, int n_fin)
{
	bool gasit = false;
	for(int i = 0; i < n_fin; i++)
		if(st_fin[i] == x)
			gasit = true;
    
	return gasit;
}

int main()
{
    ifstream f("/Users/Ioana/Desktop/XCode Projects/Tema 2- LFA- Minimizarea unui automat/Tema 2- LFA- Minimizarea unui automat/date.txt");
    
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
    
    int tranzitii[20][20]; //a = matricea de tranzitii
    int j, k = 1, x;
    int nr_tranzitii;
    f >> nr_tranzitii; //citeste nr de tranzitii
    for (i=0; i<nr_stari; i++)
        for (j=0; j<n_alfabet; j++)
            tranzitii[i][j] = -1; //initializeaza matricea de tranzitii cu -1
    while (k <= nr_tranzitii) //citeste tranzitiile din fisier (de unde pleaca, cu ce, unde ajunge)
    {
        f >> i >> x >> j;
        tranzitii[i][x] = j; //x = cu ce se face tranzitia de la i la j; x = pozitia caracterului in alfabet
        k++;
    }
//Afisarea matricei de tranzitii
    cout << "Matricea de tranzitii este: " << endl;
    for (i=0; i<nr_stari; i++)
    {
        cout << i << "| ";
        for (j=0; j<n_alfabet; j++)
            cout << tranzitii[i][j] << " ";
        cout << endl;
    }
    
    
    int elim[30];
	char mini[30][30];
    
    for (i=0; i<nr_stari; i++) //vector ce retine daca starea trebuie eliminata sau nu; initial, consideram
		elim[i] = 0; //ca putem elimina toate starile
	elim[st_in] = 1; //starea initiala nu va fi niciodata eliminata
    
    for (i=0; i<nr_stari; i++)// verific dak starile sunt accesibile sau nu si notez in h
        for (j=0; j<n_alfabet; j++)
            if (tranzitii[i][j] != -1) //-1 inseamna ca din starea i cu elementul j din alfabet nu ajung nicaieri
                elim[tranzitii[i][j]] = 1;
    
/* Afisez vectorul elim dupa ce am marcat starile inaccesibile
    for(i=0; i<nr_stari; i++)
        cout << elim[i] << " ";*/
    
    for (i=0; i<nr_stari; i++) // elimin starile inaccesibile; daca elim[i] = 0, inseamna ca e inaccesibila
		if(elim[i] == 0)
            for(j=1; j<n_alfabet; j++)
                tranzitii[i][j] = -1;
    
    for (i=0; i<nr_stari; i++) // initializez matrice minimizare
		for(j=0; j<nr_stari; j++)
			mini[i][j] = '-';
    for (i=0; i<nr_stari; i++)
        for (j=0; j<nr_stari; j++)
        {
            if (apartine(st_fin, i, n_fin) == true && apartine(st_fin, j, n_fin) == false)
                mini[i][j] = '*';
            if (apartine(st_fin, i, n_fin) == false && apartine(st_fin, j, n_fin) == true)
                mini[i][j] = '*';
        }
            
//Afisez matricea de minimizare
    cout << "Matrice marcata doar cu starile finale:" << endl;
	for (i=0; i<nr_stari; i++) // afisare matrice minimizare
	{
        if (i == 0) cout << mini[0][0];
		for(j=0; j<i; j++)
			cout << mini[i][j] << " ";
		cout << endl;
	}
    
    int a1, a2;
	bool gasit = true;
    while(gasit == true) //marchez in matricea minimizare pana cand nu imi mai modifica nimic
	{
		gasit = false;
		for(i=0; i<nr_stari; i++) //i ia la rand toate liniile
			for(j=0; j<i; j++) //j ia toate coloanele din triunghiul inferior
			{
				if(mini[i][j] != '*') //daca n-a fost inca marcat cu *
				{
                    for (k=0; k<n_alfabet; k++)
                    {
                        a1 = tranzitii[i][k]; //a1 = starea in care ajunge din i cu elementul k din alfabet
                        a2 = tranzitii[j][k]; //a2 = idem a1
                        if (mini[a1][a2] == '*') //daca starea a2 e finala si starea a1 nu e finala
                        {
                            mini[i][j] = '*';
                            gasit = true;
                        }
                    }
				}
			}
	}
    
//Afisez matricea de minimizare modificata
    cout << endl << "Matrice de minimizare modificata:" << endl;
	for (i=0; i<nr_stari; i++) // afisare matrice minimizare
	{
        if(i == 0) cout << mini[0][0];
		for(j=0; j<i; j++)
			cout << mini[i][j] << " ";
		cout << endl;
	}

//Parcurg matricea de minimizare din nou pentru a marca in vectorul elim (care retine daca o stare trebuie eliminata sau nu) starile echivalente
	for (i=0; i<nr_stari; i++) // unde exista '-' in matricea minimizare atunci notez in elim ca pot eliminate
		for(j=0; j<i; j++)
			if(mini[i][j] == '-')
				elim[i] = 0;
    
//Afisez nodurile eliminate
	cout << endl << "Starile eliminate sunt: ";
	for(i=0; i<nr_stari; i++)
		if(elim[i] == 0)
			cout << "q" << i << " ";
	cout << endl;
    
//Afisez noul automat minimizat cu starile echivalente eliminate
	for (i=0; i<nr_stari; i++)
		if (elim[i] == 1)
            for (k=0; k<n_alfabet; k++)
            {
                
                cout << "(" << i << ", " << alfabet[k] << ") -> ";
                if (!elim[tranzitii[i][k]])
                {
                    for(j=0; j<tranzitii[i][k]; j++)
                        if (mini[tranzitii[i][k]][j] == '-')
                            cout << j << endl;
                }
                else cout << tranzitii[i][k]<< endl;
            }

    return 0;
}

