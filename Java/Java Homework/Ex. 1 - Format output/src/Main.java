import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args)
    {   
        Scanner Sc = null;
        try {
           Sc = new Scanner(new File("input.txt"));
           ArrayList<String> names = new ArrayList<String>();
           ArrayList<Integer> numbers = new ArrayList<Integer>();
           while(Sc.hasNext())
           {
               String s = Sc.nextLine();
               if(s.charAt(0) >= '0' && s.charAt(0) <= '9')
               {
                   int x = Integer.parseInt(s);
                   numbers.add(x);
               }
               else 
                   names.add(s);
           }
           System.out.println(String.format("%-20s %-20s", "Surname", "Payroll No."));
           for(int i=0; i<names.size(); i++)
               System.out.println(String.format("%-20s %-20s", names.get(i), numbers.get(i)));
        }
        catch (FileNotFoundException e) {
            System.out.println("The file was not found!"); 
        }
        finally {Sc.close();}
    }
}
