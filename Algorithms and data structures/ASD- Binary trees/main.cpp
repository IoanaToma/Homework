#include <iostream>

using namespace std;

struct nod
{
    int info;
    nod *st;
    nod *dr;
};

void adaug_frunza_st (nod *rad, int x)
{
    nod *q;
    q = new nod;
    q->info = x;
    q->st = NULL;
    q->dr = NULL;
    rad->st = q;
}

void adaug_frunza_dr (nod *rad, int x)
{
    nod *q;
    q = new nod;
    q->info = x;
    q->st = NULL;
    q->dr = NULL;
    rad->dr = q;
}

void RSD (nod *rad)
{
    cout << rad->info << " ";
    if (rad->st)
        RSD (rad->st);
    if (rad->dr)
        RSD (rad->dr);

}

void SRD (nod *rad)
{
    if (rad->st)
        SRD (rad->st);
    cout << rad->info << " ";
    if (rad->dr)
        SRD (rad->dr);

}

void SDR (nod *rad)
{
    if (rad->st)
        SDR (rad->st);
    if (rad->dr)
        SDR (rad->dr);
    cout << rad->info << " ";

}

int main()
{
    nod *rad;
    int x, y;
    rad = new nod;
    cout << "Dati radacina arborelui:";
    cin >> rad->info;
    rad->st = NULL;
    rad->dr = NULL;

    cout << "Dati valoarea unui nou nod de tip frunza:";
    cin >> x;
    adaug_frunza_st(rad, x);

    cout << "Dati valoarea unui nou nod de tip frunza:";
    cin >> y;
    adaug_frunza_dr(rad, y);

    SRD (rad);
    cout << endl;
    RSD (rad);
    cout << endl;
    SDR (rad);


    return 0;
}
