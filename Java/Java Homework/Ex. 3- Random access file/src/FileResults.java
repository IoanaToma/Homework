import java.io.*;
import java.util.*;

public class FileResults 
{
    private static final long REC_SIZE = 34;
    private static final int SURNAME_SIZE = 15;
    private static String surname;
    private static int mark;
    
    public static void main(String[] args) throws IOException 
    {
        ArrayList<String> names = new ArrayList<String>();
        ArrayList<Integer> marks = new ArrayList<Integer>();
        Scanner Sc = new Scanner(new File("names.txt"));
        while(Sc.hasNext())
        {
            String s = Sc.nextLine();
            if(s.charAt(0) >= '0' && s.charAt(0) <= '9')
            {
                int x = Integer.parseInt(s);
                marks.add(x);
            }
            else
                names.add(s);
        }
        
        RandomAccessFile myFile = new RandomAccessFile("results.dat", "rw");
        for(int i=0; i<names.size(); i++)
        {
            surname = names.get(i);
            mark = marks.get(i);
            writeRecord(myFile, i+1);
        }
        
        myFile.seek(0);
        for(int i=1; i<=names.size(); i++)
            readRecord(myFile, i);
    }
    
    public static void writeString(RandomAccessFile file, String text, int fixedSize) 
            throws IOException 
    {
        int size = text.length();
        if (size <= fixedSize) 
        {
            file.writeChars(text);
            for (int i = size; i < fixedSize; i++) 
                file.writeChar(' ');
        }
        else 
            file.writeChars(text.substring(0, fixedSize));
    }
    
    public static void writeRecord(RandomAccessFile file, int recPos)
            throws IOException
    {
        file.seek((recPos - 1) * REC_SIZE);
        writeString(file, surname, SURNAME_SIZE);
        file.writeInt(mark);
    }
    
    public static String readString(RandomAccessFile file, int fixedSize)
            throws IOException 
    {
        String value = "";
        for (int i = 0; i < fixedSize; i++) 
            value += file.readChar();
        return value;
    }
    
    public static void readRecord(RandomAccessFile file, int recPos)
            throws IOException
    {   
        file.seek((recPos - 1) * REC_SIZE);
        surname = readString(file, SURNAME_SIZE);
        mark = file.readInt();
        System.out.println(surname + " " + mark);
    }
}