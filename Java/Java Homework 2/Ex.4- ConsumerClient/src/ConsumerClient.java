import java.io.*;
import java.net.*;
import java.util.*;
 
public class ConsumerClient
{
    private static InetAddress host;
    private static final int PORT = 1234;
 
    public static void main(String[] args)
    {
        try
        {
            host = InetAddress.getLocalHost();
        }
        catch(UnknownHostException uhEx)
        {
            System.out.println("\nHost ID not found!\n");
            System.exit(1);
        }
        retrieveResource();
    }
 
    private static void retrieveResource()
    {
        Socket socket = null;
 
        try
        {
            socket = new Socket(host,PORT);
 
            Scanner in = new Scanner(socket.getInputStream());
            PrintWriter out = new PrintWriter(socket.getOutputStream(),true);
            Scanner userEntry = new Scanner(System.in);
 
            String message, response;
            do
            {
                System.out.print("Enter message (1 to get a resource from the producer, "
                        + "0 when you've had enough): ");
                message =  userEntry.nextLine();
                if(!message.equals("1") && !message.equals("0"))
                    System.out.println("\nThe producer could not process your request.. Try again!\n");
                else
                {
                    try
                    {
                        out.println(message);
                        response = in.nextLine();
                        System.out.println("Producer: " + response);
                    }
                    catch(NoSuchElementException n)
                    {}
                }
            }while (!message.equals("0"));
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }
        finally
        {
            try
            {
                System.out.println("Thank you for shopping with us!");
                socket.close();
            }
            catch(IOException e)
            {
                System.out.println("Unable to disconnect!");
                System.exit(1);
            }
        }
    }
}