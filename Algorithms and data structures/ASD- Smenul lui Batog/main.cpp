#include <iostream>
#include <math.h>

using namespace std;

int minim (int v[200], int x, int y)
{
    int i, m = x;
    for (i=x+1; i<y; i++)
        if (v[i] < v[m])
            m = i;
    return m;

}

int main()
{
    int v[200], poz_min[15], v_sortat[200], n, l, i, j, m, k, infinit;
    cout << "Dati numarul de elemente ale vectorului:";
    cin >> n;
    cout << "\nDati elementele vectorului:";
    for (i=0; i<n; i++)
        cin >> v[i];
    infinit = 20000000;
    l = sqrt (n);
    i = 0;
    k = 0;
    while(i+l <= n)
    {
        poz_min[k] = minim (v, i, i+l);
        i = i+l;
        k = k+1;
    }
    if (i < n)
    {
        poz_min[k] = minim (v, i, n);
        k = k+1;
    }

    for (i=0; i<n; i++)
    {
        m = 0;
        for (j=0; j<k; j++) if(v[poz_min[j]] < v[poz_min[m]]) m = j;

        v_sortat[i] = v[poz_min[m]];
        v[poz_min[m]] = infinit;

        if(m*l+l > n) poz_min[m] = minim (v, m*l, n);
        else poz_min[m] = minim (v, m*l, m*l+l);

    }
    cout << "\n\nVectorul sortat : ";
    for (i=0; i<n; i++) cout << v_sortat[i] << " ";

    return 0;
}
