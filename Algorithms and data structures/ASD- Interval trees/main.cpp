#include <iostream>

using namespace std;

int v[100], arb[200];

int minim (int a, int b)
{
    if (a <b) return a;
    else return b;
}

int create (int poz, int st, int dr)
{
    if (st == dr)
    {
        arb[poz] = v[st];
        return arb[poz];
    }
    arb [poz] = minim (create (poz*2, st, (st + dr)/2), create (poz*2, (st + dr)/2, dr));
    return arb[poz];
}

int main()
{
    int i, n, poz, st, dr;
    cout << "Dati numarul de elemente ale vectorului:";
    cin >> n;
    cout << "Dati elementele vectorului:";
    for (i=0; i<n; i++)
        cin >> v[i];

    poz = 0;
    st = 1;
    dr = n;
    create (poz, st, dr);

    return 0;
}
