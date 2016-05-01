#include <iostream>

using namespace std;

struct nod
{
    int info;
    nod *ante;
    nod *urm;
};

void creare (nod *&prim_coada, nod *&ultim_coada)
{
    nod *q;
    q = new nod;
    cout << "Dati urmatorul nod:";
    cin >> q->info;
    q->ante = NULL;
    q->urm = NULL;
    if (!prim_coada)
    {
        prim_coada = q;
        ultim_coada = prim_coada;
    }
    else
    {
        ultim_coada->urm = q;
        q->ante = ultim_coada;
        ultim_coada = q;
    }
}

void afisare_st_dr (nod *prim_coada)
{
    nod *p;
    p = prim_coada;
    while (p)
    {
        cout << p->info << " ";
        p = p->urm;
    }
}

void inserare_inc(nod *&prim_coada)
{
    nod *q;
    q = new nod;
    cout << "Dati noul nod:";
    cin >> q->info;
    q->ante = NULL;
    q->urm = prim_coada;
    prim_coada->ante = q;
    prim_coada = q;
}

void inserare_sf(nod *&ultim_coada)
{
    nod *q;
    q = new nod;
    cout << "Dati noul nod:";
    cin >> q->info;
    q->ante = ultim_coada;
    q->urm = NULL;
    ultim_coada->urm = q;
    ultim_coada = q;
}

void stergere_inc (nod *&prim_coada)
{
    nod *p;
    p = prim_coada;
    prim_coada = prim_coada->urm;
    prim_coada->ante = NULL;
    delete p;
}

void stergere_sf (nod *&ultim_coada)
{
    nod *p;
    p = ultim_coada;
    ultim_coada = ultim_coada->ante;
    ultim_coada->urm = NULL;
    delete p;
}

void meniu ()
{
    cout << "Optiunile dumneavoastra sunt:" << endl;
    cout << "1. Adaugarea unui element la inceput" << endl;
    cout << "2. Adaugarea unui element la sfarsit" << endl;
    cout << "3. Stergerea primului element" << endl;
    cout << "4. Stergerea ultimului element" << endl;
    cout << "5. Exit" << endl;
}

int main()
{
    nod *prim_coada, *ultim_coada;
    int i, n;
    cout << "Numarul de noduri ale cozii va fi:";
    cin >> n;
    prim_coada = NULL;
    for (i=0; i<n; i++)
        creare(prim_coada, ultim_coada);
    cout << "Coada este:";
    afisare_st_dr(prim_coada);
    cout << endl;

    meniu();

    int x;
    cout << "Alegerea dumneavoastra este: ";
    cin >> x;

    while (x != 5)
        {
             switch (x)
            {
                case 1:
                    inserare_inc(prim_coada);
                    afisare_st_dr(prim);
                    cout << endl;
                    break;
                case 2:
                    inserare_sf(ultim_coada);
                    afisare_st_dr(prim);
                    cout << endl;
                    break;
                case 3:
                    stergere_inc(prim_coada);
                    afisare_st_dr(prim);
                    cout << endl;
                    break;
                case 4:
                    stergere_sf(prim_coada);
                    afisare_st_dr(prim);
                    cout << endl;
                    break;
                case 5:
                    return 0;
            }
            cin >> x;
        }
}
