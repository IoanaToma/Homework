import java.util.*;

/*
 * p1 = 4, t1 = 3 
 * p2 = 1, t2 = 1 
 * p3 = 2, t3 = 1 
 * p4 = 5, t4 = 3
 */

class Activity implements Comparable<Activity>
{
	int deadline, duration, profit;
	
	Activity()
	{
		deadline = duration = profit = 0;
	}
	
	Activity(int d, int t, int p)
	{
		deadline = d;
		duration = t;
		profit = p;
	}

	@Override
	public int compareTo(Activity a) {
		if(deadline > a.deadline) return 1;
		else if(deadline < a.deadline) return -1;
		return 0;
	}
}

public class Main {
	static void printPlan(int[][] A, ArrayList<Activity> list,  int i, int t)
	{
		if(i == 0) return;
		if(A[i][t] == A[i-1][t])
			printPlan(A, list, i-1, t);
		else
		{
			int t1 = Math.min(t, list.get(i).deadline) - list.get(i).duration;
			printPlan(A, list, i-1, t1);
			System.out.print(i + " ");
		}
	}
	
	public static void main(String[] args)
	{
		Scanner Sc = new Scanner(System.in);
		ArrayList<Activity> list = new ArrayList<Activity>();
		System.out.print("Dati numarul de activitati: ");
		int n = Sc.nextInt();
		Activity a = new Activity();
		list.add(a);
		for(int i=0; i<n; i++)
		{
			int d = Sc.nextInt();
			int t = Sc.nextInt();
			int p = Sc.nextInt();
			Activity ac = new Activity(d, t, p);
			list.add(ac);
		}
		
		Collections.sort(list);
		
		/*for(int i=1; i<=n; i++)
			System.out.print(list.get(i).profit + " ");*/
		
		int d = list.get(list.size()-1).deadline;
		
		int[][] A = new int[n+1][d+1];
		for(int i=0; i<=d; i++)
			A[0][i] = 0;
		for(int i=1; i<=n; i++)
			for(int t=0; t<=d; t++)
			{
				int t1 = Math.min(t, list.get(i).deadline) - list.get(i).duration;
				if(t1 < 0)
					A[i][t] = A[i-1][t];
				else
					A[i][t] = Math.max(A[i-1][t], list.get(i).profit + A[i-1][t1]);
			}
		
		System.out.println("Profitul maxim este: " + A[n][d]);
		
		printPlan(A, list, n, d);
	}
}
