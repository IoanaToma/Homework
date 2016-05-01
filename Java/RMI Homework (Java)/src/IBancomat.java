import java.rmi.*;

public interface IBancomat extends Remote
{   
    public boolean withdrawCash(int myMoney) throws RemoteException;
    public void depositCash(int myMoney) throws RemoteException;
    public String seeBalance() throws RemoteException;
    
}
