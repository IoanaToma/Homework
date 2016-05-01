#include <stdio.h>
#include <stdlib.h>

void afisare (int v[200], int n)
{
    int i;
    for (i=0; i<n; i++)
         printf ("%d ", v[i]);
}

void interclasare (int v[200], int inc, int fin)
{
    int dr[100], st[100], p, n = 0, m = 0, k, i, j;
    p = (inc + fin)/2;
    for (k=inc; k<=p; k++)
        dr[n++] = v[k];
    for (k=p+1; k<=fin; k++)
        st[m++] = v[k];
    k = inc;
    i = 0;
    j = 0;
    while (i<n && j<m)
        if (dr[i] <= st[j])
        {
            v[k++] = dr[i];
            i++;
        }
        else
        {
            v[k++] = st[j];
            j++;
        }
    while (i < n)
    {
        v[k++] = dr[i];
        i++;
    }
    while (j < m)
    {
        v[k++] = st[j];
        j++;
    }
}

void mergesort (int v[200], int inc, int fin)
{
    if (inc < fin)
    {
        int p;
        p = (inc + fin)/2;
        mergesort (v, inc, p);
        mergesort (v, p+1, fin);
        interclasare (v, inc, fin);
    }
}

int main()
{
    int v[200], n, i;
    scanf ("%d", &n);
    for (i=0; i<n; i++)
        scanf ("%d", &v[i]);
    mergesort (v, 0, n-1);
    afisare(v, n);

    return 0;
}
