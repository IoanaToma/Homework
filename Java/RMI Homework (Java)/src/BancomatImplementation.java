import java.rmi.*;
import java.rmi.server.*;

public class BancomatImplementation extends UnicastRemoteObject implements IBancomat
{   
    public int sold;
    
    public BancomatImplementation() throws RemoteException
    {
        sold = 200;
    }
    
    @Override
    public boolean withdrawCash(int myMoney) throws RemoteException
    {
        if(sold >= myMoney)
        {
            sold = sold - myMoney;
            return true;
        }
        return false;
    }
    
    @Override
    public void depositCash(int myMoney) throws RemoteException
    {
        sold = sold + myMoney;
    }
    
    @Override
    public String seeBalance() throws RemoteException
    {
        return "Soldul dumneavoastra este: " + sold + " lei.";
    }
}
