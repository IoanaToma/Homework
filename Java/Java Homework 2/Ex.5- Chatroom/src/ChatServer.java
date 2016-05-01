import java.io.*;
import java.net.*;
import java.util.*;

public class ChatServer {
    private static ServerSocket serverSocket;
    private static final int PORT = 1234;
 
    public static void main(String[] args)
    {
        try
        {
            serverSocket = new ServerSocket(PORT);
        }
        catch (IOException e)
        {
            System.out.println("There was a problem setting up the port..");
            System.exit(1);
        }
        
        System.out.println("Server set up, waiting for clients!");
        
        do
        {
            Socket client = null;
            try 
            {
                client = serverSocket.accept();
            } 
            catch (IOException ex) 
            {
                System.out.println("The server could not accept the client!");
            }
            
            Connection handler = new Connection(client);
            handler.start();
            
        }while (true);
    }
}

class Connection extends Thread
{
    Socket client;
    String nickname;
    Scanner in;
    PrintWriter out;
 
    public Connection(Socket socket)
    {
        client = socket;
 
        try
        {
            in = new Scanner(client.getInputStream());
            out = new PrintWriter(client.getOutputStream(),true);
        }
        catch(IOException e){}
    }
 
    public void run()
    {
        nickname = in.nextLine();
        System.out.println(nickname + " is now connected!");
        Memory.usersList.add(this);
        Memory.broadcastNameToOthers(nickname);
        
        for(int i=0; i<Memory.usersList.size(); i++)
        {
            Connection c = Memory.usersList.get(i);
            if(!c.nickname.equals(nickname))
                out.println(c.nickname + " is now connected!");
        }
        
        String message;
        do
        {
            message = in.nextLine();
            Memory.broadcast(message);
            
        }while(!message.contains("Bye!"));
        
        Memory.broadcast(nickname + " is now disconnected!");
        System.out.println(nickname + " is now disconnected!");
        
        for(int i=0; i<Memory.usersList.size(); i++)
            if(Memory.usersList.get(i).nickname == this.nickname)
            {
                Memory.usersList.remove(i);
                break;
            }
        
        this.interrupt();
    }
}

class Memory
{
    static ArrayList<Connection> usersList = new ArrayList<Connection>();
    
    synchronized static void broadcast(String s)
    {
        Connection c;
        for(int i=0; i<usersList.size(); i++)
        {
            c = usersList.get(i);
            c.out.println(s);
        }
    }
    
    synchronized static void broadcastNameToOthers(String name)
    {
        Connection c;
        for(int i=0; i<usersList.size(); i++)
        {
            c = usersList.get(i);
            if(!c.nickname.equals(name))
                c.out.println(name + " is now connected!");
        }
    }
}
