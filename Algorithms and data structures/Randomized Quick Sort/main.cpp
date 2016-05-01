#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

void quicksort(int v[20], int inc, int fin)
{
      int i, j, p, t, piv;
      i = inc;
      j = fin;
      srand (time(0));
      piv = rand()%fin;
      while (piv < inc || piv > fin)
        piv = rand()%fin;
      p = v[piv];
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
    cout << "Dati n:";
    cin >> n;
    for(i=0; i<n; i++)
        cin >> v[i];

    quicksort(v, 0, n-1);

    for(i=0; i<n; i++)
        cout << v[i] << " ";

    return 0;
}
