import java.util.Scanner;

//v = -2 3 -1 7 11 -2 3 -6 5
//rezultat: 3 -1 7 11 -2 3

class Main
{
	static void maximumSumSubsequence(int[] v) 
	{
	    int maxSum = Integer.MIN_VALUE;
	    int finalStartIndex = 0;
	    int finalEndIndex = 0;
	    int currentSum = 0;
	    int currentStartIndex = 0;

	    for (int i=0; i<v.length; i++) 
	    {
	        currentSum += v[i];
	        if (currentSum > maxSum) {
	            maxSum = currentSum;
	            finalEndIndex = i;
	            finalStartIndex = currentStartIndex;
	        }
	        if (currentSum <= 0) {
	            currentSum = 0;
	            currentStartIndex = i + 1;
	        }
	    }
	    System.out.println("Suma maxima ce se poate obtine din vector este: " + maxSum);
	    System.out.println("Subsecventa incepe de pe pozitia " + finalStartIndex + " si se termina pe pozitia " + finalEndIndex);
	}
	
	public static void main(String[] args)
	{
		Scanner Sc = new Scanner(System.in);
		System.out.print("Dati dimensiunea vectorului: ");
		int n = Sc.nextInt();
		int v[] = new int[n];
		System.out.println("Dati vectorul : ");
		for(int i=0; i<n; i++)
			v[i] = Sc.nextInt();
		maximumSumSubsequence(v);
	}
}
