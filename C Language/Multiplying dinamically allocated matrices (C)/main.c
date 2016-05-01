#include <stdio.h>
#include <stdlib.h>

int main()
{
    int **a, **b, **c, n, i, j, k1, s;
    printf ("Dati n:");
    scanf ("%d", &n);

    a = malloc (n*sizeof(int*));
    for (i=0; i<n; i++)
        a[i] = malloc ((i+2)*sizeof(int)+1);
    printf ("Dati elementele matricei a (triunghiulara inferior): ");
    for (i=0; i<n; i++)
        for (j=0; j<i+1; j++)
                scanf ("%d", &a[i][j]);
    for (i=0; i<n; i++)
        {
            for (j=0; j<i+1; j++)
                printf ("%d ", a[i][j]);
            printf ("\n");
        }

    printf ("\n\n");
    b = malloc (n*sizeof(int*));
    for (i=0; i<n; i++)
        b[i] = malloc ((n-i+1)*sizeof(int)+1);
    printf ("Dati elementele matricei b (triunghiulara superior): ");
    for (i=0; i<n; i++)
        for (j=i; j<n; j++)
                scanf ("%d", &b[i][j]);
    for (i=0; i<n; i++)
        {
            for (j=i; j<n; j++)
                printf ("%d ", b[i][j]);
            printf ("\n");
        }

    c = malloc ((n+1)*sizeof(int*));
    for (i=0; i<n; i++)
        c[i] = malloc ((n+1)*sizeof(int));
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
        {
            k1 = 0;
            s = 0;
            while (k1 < (i+1) && k1 < (j+1))
            {
                s = s + a[i][k1] * b[k1][j];
                k1++;
            }
            c[i][j] = s;
        }

    printf ("\nMatricea rezultata prin inmultirea celor doua este:\n");
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
                printf ("%d ", c[i][j]);
        printf ("\n");
    }


    return 0;
}
