import java.io.*;
import java.net.*;
import java.util.*;
 
class ClientThread extends Thread
{
   private Socket client;
   private Resource item;
   private Scanner input;
   private PrintWriter output;
 
   public ClientThread(Socket socket, Resource resource)
   {
      client = socket;
      item = resource;
 
      try
      {
         //Create input and output streams on the socket...
         input = new Scanner(client.getInputStream());
         output = new PrintWriter(
                            client.getOutputStream(),true);
      }
      catch(IOException ioEx)
      {
         ioEx.printStackTrace();
      }
   }
 
    public void run()
    {
        String request = "";
 
        do
        {
            request = input.nextLine();
            if (request.equals("1"))
            {
               item.takeOne();//If none available,
                              //wait until resource(s)
                              //available (and thread is
                              //at front of thread queue).
               output.println("Request granted.");
            }
        }while (!request.equals("0"));
 
        try
        {
            System.out.println(
                        "Closing down connection...");
            client.close();
        }
        catch(IOException ioEx)
        {
            System.out.println(
                "Unable to close connection to client!");;
        }
    }
}