#include <stdio.h>
#include <stdlib.h>

void quicksort(int v[20], int inc, int fin)
{
      int i, j, p, t;
      i = inc;
      j = fin;
      p = v[(inc + fin)/2];
      while (i <= j)
        {
            while (v[i] < p)
                i++;
            while (v[j] > p)
                j--;
            if (i <= j)
            {
                t = v[i];
                v[i] = v[j];
                v[j] = t;
                i++;
                j--;
            }
        };

      if (inc < j)
            quicksort(v, inc, j);
      if (i < fin)
            quicksort(v, i, fin);
}

int main()
{

    int v[20],i,n;
    printf ("Dati n:");
    scanf("%d", &n);
    printf ("Dati elementele vectorului:");
    for(i=0; i<n; i++)
        scanf("%d", &v[i]);

    quicksort(v, 0, n-1);

    for(i=0; i<n; i++)
        printf("%d ", v[i]);


  return 0;
}
