import java.io.*;
import java.util.*;

class Person implements Serializable
{
    String name, surname;
    Person() 
    {
        surname = name = "";
    }
    Person(String s1, String s2)
    {
        name = s1;
        surname = s2;
    }
}
        
public class Main {
    public static void main(String[] args)
    {   
        ObjectOutputStream out = null;
        ObjectInputStream in = null;
        try{
            out = new ObjectOutputStream(new FileOutputStream("persons.dat"));
            ArrayList<Person> list = new ArrayList<Person>();
            list.add(new Person("Jane", "Eyre"));
            list.add(new Person("John", "Smith"));
            list.add(new Person("Ed", "Sheeran"));
            for (int i=0; i<list.size(); i++)
                out.writeObject(list.get(i));
            out.close();
            
            in = new ObjectInputStream(new FileInputStream("persons.dat"));
            try
            {
                do
                {
                    Person p;
                    p = (Person)in.readObject();
                    System.out.print(p.name + ' ' + p.surname + "\n");
                }while (true);
            }
            catch (EOFException e)
            {
                System.out.println("\nYou've reached the end of the file!");
                in.close();
            }
            catch(ClassNotFoundException c)
            {
                System.out.println("Something went wrong!");
                in.close();
            }
            
        }
        catch(IOException e)
        {
            System.out.println("Exception caught!");
        }
        finally {}
    }
}
