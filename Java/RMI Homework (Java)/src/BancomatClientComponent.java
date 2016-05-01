import java.rmi.*;
import java.util.*;

public class BancomatClientComponent {
    public static void main(String[] args) throws Exception
    {   
        System.out.println("Bine ati venit!");
        
        IBancomat bancomat = (IBancomat) Naming.lookup("rmi://" + 
                "localhost" + "/BancomatImplementation");
        Scanner Sc = new Scanner(System.in);
        
        int choice;
        do
        {
            System.out.println("Optiunile disponibile sunt(alegeti un numar): ");
            System.out.println("1. Retragere numerar \n2. Depunere numerar "
                    + "\n3. Vizualizare sold \n0. Iesire");
            System.out.print("Optiunea dumneavoastra este: ");
            choice = Sc.nextInt();
            
            float sum;
            switch(choice)
            {
                case 1 :
                    System.out.print("Introduceti suma pe care doriti sa o retrageti: ");
                    sum = Sc.nextFloat();
                    
                    while(sum != (int)sum)
                    {
                        System.out.println("Nu puteti retrage decat sume intregi (fara virgula)."
                                + "Incercati din nou: ");
                        sum = Sc.nextFloat();
                    }
                    
                    if(bancomat.withdrawCash((int)sum) == false)
                        System.out.println("Ne pare rau, fonduri insuficiente!");
                    else 
                        System.out.println("Ati retras suma de " + (int)sum + " lei. "
                                + "Va rugam ridicati numerarul!");
                    break;
                    
                case 2 :
                    System.out.print("Introduceti suma pe care doriti sa o depuneti: ");
                    sum = Sc.nextFloat();
                    
                    while(sum != (int)sum)
                    {
                        System.out.println("Nu puteti depune decat sume intregi (fara virgula)."
                                + "Incercati din nou: ");
                        sum = Sc.nextFloat();
                    }
                    
                    bancomat.depositCash((int)sum);
                    System.out.println("Ati depus suma de: " + (int)sum + " lei.");
                    break;
                
                case 3 :
                    System.out.println(bancomat.seeBalance());
                    break;
                
                case 0 : 
                    System.out.println("\nVa multumim! Ridicati cardul..\n");
                    break;
                    
                default: 
                    System.out.println("Eroare! Incercati tastarea din nou: ");
                    break;
            } 
            System.out.println();
            
        }while(choice != 0);
    }
}
