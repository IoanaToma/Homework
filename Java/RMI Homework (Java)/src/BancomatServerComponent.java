import java.rmi.*;

public class BancomatServerComponent {
    public static void main(String[] args) throws Exception
    {
        BancomatImplementation bi = new BancomatImplementation();
        String objName = "rmi://" + "localhost" + "/BancomatImplementation";
        Naming.bind(objName, bi);
        System.out.println("Server is ready!");
    }
}
