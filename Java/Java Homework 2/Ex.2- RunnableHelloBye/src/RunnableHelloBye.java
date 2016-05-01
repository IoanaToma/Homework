public class RunnableHelloBye {
    public static void main(String[] args)
    {
        Thread hello = new Thread(new Hello());
        Thread bye = new Thread(new Goodbye());
        hello.start();
        bye.start();
    }
}

class Hello implements Runnable
{
    @Override
    public void run() 
    {
        int pause;
        for (int i=0; i<10; i++) 
            try 
            {
                System.out.println("Hello!");
                pause = (int)(Math.random() * 2000);
                Thread.sleep(pause);
            } 
            catch (InterruptedException e) 
            {
                System.out.println(e);
            }
    }
}
 
class Goodbye implements Runnable 
{
    @Override
    public void run() 
    {   
        int pause;
        for (int i=0; i<10; i++) 
            try 
            {
                System.out.println("Goodbye!");
                pause = (int)(Math.random() * 2000);
                Thread.sleep(pause);
            } 
            catch (InterruptedException e) 
            {
                System.out.println(e);
            }
    }
}
