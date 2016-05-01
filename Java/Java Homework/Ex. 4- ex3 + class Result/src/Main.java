import java.io.*;
import java.util.*;

class Result implements Serializable 
{
    private String surname;
    private int mark;
    
    public Result(String name, int score) 
    {
        surname = name;
        mark = score;
    }
    
    public String getName() 
    {
        return surname;
    }
    
    public void setName(String name) 
    {
        surname = name;
    }
    
    public int getMark() 
    {
        return mark;
    }
    
    public void setMark(int score) 
    {
        if ((score >= 0) && (score <= 100)) 
            mark = score;
    }
}

public class Main {
    private static final long REC_SIZE = 34;
    private static final int SURNAME_SIZE = 15;
    
    public static void main(String[] args) throws IOException
    {
        ArrayList<Result> res = new ArrayList<Result>();
        Scanner Sc = new Scanner(new File("input.txt"));
        int j = 0;
        while(Sc.hasNext())
        {
            String s = Sc.nextLine();
            if(s.charAt(0) >= '0' && s.charAt(0) <= '9')
            {
                int x = Integer.parseInt(s);
                res.get(j).setMark(x);
                j++;
            }
            else
            {
                Result r = new Result(s, 0);
                res.add(r);
            }
        }
        
        RandomAccessFile myFile = new RandomAccessFile("results.dat", "rw");
        for(int i=0; i<res.size(); i++)
        {
            Result r = res.get(i);
            writeRecord(myFile, i+1, r);
        }
        
        myFile.seek(0);
        for(int i=1; i<=res.size(); i++)
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
    
    public static void writeRecord(RandomAccessFile file, int recPos, Result r)
            throws IOException
    {
        file.seek((recPos - 1) * REC_SIZE);
        writeString(file, r.getName(), SURNAME_SIZE);
        file.writeInt(r.getMark());
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
        Result r = new Result("", 0);
        r.setName(readString(file, SURNAME_SIZE));
        r.setMark(file.readInt());
        System.out.println(r.getName() + " " + r.getMark());
    }
}
