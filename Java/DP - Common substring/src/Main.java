import java.util.Scanner;

//a = 15 2 11 10 4 1 7 
//b = 4 2 3 1 7 10 1 12 5 6 7 9 4
//rezultat: 2 10 1 7

public class Main 
{
	static void LCS(int a[], int b[])
	{	
		int m = a.length;
		int n = b.length;
		int l[][] = new int[m+1][n+1];
	 
	   for (int i=0; i<=m; i++)
	   {
	     for (int j=0; j<=n; j++)
	     {
	       if (i == 0 || j == 0)
	         l[i][j] = 0;
	       else if (a[i-1] == b[j-1])
	         l[i][j] = l[i-1][j-1] + 1;
	       else
	         l[i][j] = Math.max(l[i-1][j], l[i][j-1]);
	     }
	   }
	 
	   int index = l[m][n];
	   System.out.print("Lungimea celui mai lung subsir comun este: ");
	   System.out.println(index);
	 
	   int lcs[] = new int[index];
	   int i = m, j = n;
	   while (i > 0 && j > 0)
	   {
	      if (a[i-1] == b[j-1])
	      {
	          lcs[index-1] = a[i-1]; 
	          i--; j--; index--;     
	      }
	      else if (l[i-1][j] > l[i][j-1])
	         i--;
	      		else
	      			j--;
	   }
	 
	   System.out.print("Cel mai lung subsir al lui a si b este: ");
	   for(i=0; i<l[m][n]; i++)
		   System.out.print(lcs[i] + " ");
	}
	 
	public static void main(String[] args)
	{
		Scanner Sc = new Scanner(System.in);
		System.out.print("Dati dimensiunea lui a: ");
		int m = Sc.nextInt();
		System.out.print("Dati dimensiunea lui b: ");
		int n = Sc.nextInt();
		System.out.print("Dati vectorul a: ");
		int a[] = new int[m];
		for(int i=0; i<m; i++)
			a[i] = Sc.nextInt();
		System.out.print("Dati vectorul b: ");
		int b[] = new int[n];
		for(int i=0; i<n; i++)
			b[i] = Sc.nextInt();
		LCS(a, b);
	}
}
