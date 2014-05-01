import java.rmi.*;
import javax.naming.*;

public class WarehouseServer {
    public static void main(String[] args) throws RemoteException, NamingException {
        System.out.println("Construction server implemetion ...");
        WarehouseImpl centerWarehouse = new WarehouseImpl();

        System.out.println("Binding server implemetion to registry...");
        Context namingContext = new InitialContext();
        namingContext.bind("rmi:centerWarehouse", centerWarehouse);
        System.out.println("Waiting for invocation for clinets ...");
    }
}
