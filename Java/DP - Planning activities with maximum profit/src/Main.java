import java.util.*;
/* 0 3 20
   2 6 30
   3 6 20
   2 10 30
   Profitul maxim este: 40
   Activitatile: 1 3 
 */

class Activity implements Comparable<Activity>
{
	int start, end, profit;
		
	Activity()
	{
		start = end = profit = 0;
	}
	
	Activity(int s, int e, int p)
	{
		start = s;
		end = e;
		profit = p;
	}

	@Override
	public int compareTo(Activity a) {
		if(end > a.end) return 1;
		else if(end < a.end) return -1;
		return 0;
	}
}

public class Main {
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
			int s = Sc.nextInt();
			int e = Sc.nextInt();
			int p = Sc.nextInt();
			Activity ac = new Activity(s, e, p);
			list.add(ac);
		}
		
		Collections.sort(list);
		
		int[] H = new int[n+1];
		H[0] = 0;
		for(int i=1; i<=n; i++)
		{
			int left = 1;
			int right = i-1;
			int mid = (left + right)/2;
			while(right - left > 1)
				if(list.get(i).start > list.get(mid).end)
				{
					left = mid + 1;
					mid = (left + right)/2;
				}
				else
				{
					right = mid - 1;
					mid = (left + right)/2;
				}
			if(right == 0) 
				H[i] = 0;
			else
				H[i] = right-1;
		}
		
		int[] A = new int[n+1];
		A[0] = 0;
		for(int i=1; i<=n; i++)
			if(A[i-1] > list.get(i).profit + A[H[i]])
				A[i] = A[i-1];
			else
				A[i] = list.get(i).profit + A[H[i]];
		
		System.out.println("Profitul maxim este: " + A[n]);
	}
}
