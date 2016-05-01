
import static java.lang.Thread.sleep;

class Producer extends Thread
{
    private Resource item;
 
    Producer(Resource resource)
    {
        item = resource;
    }
 
    public void run()
    {
        int pause;
        int newLevel;
 
        do
        {
            try
            {
                //Add 1 to level and return new level...
                newLevel = item.addOne();
                System.out.println(
                     "<Producer> New level: " + newLevel);
                pause = (int)(Math.random() * 5000);
 
                //'Sleep' for 0-5 seconds...
                sleep(pause);
            }
            catch (InterruptedException interruptEx)
            {
                System.out.println(interruptEx.toString());
            }
        }while (true);
    }
}