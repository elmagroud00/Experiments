import java.rmi.*;
import java.util.*;
import javax.naming.*;

public class WarehouseClient {
    public static void main(String[] args) throws NamingException, RemoteException {
        Context namingContext = new InitialContext();
        System.out.println("RMI registy bindings: ");
        Enumeration<NameClassPair> e = namingContext.list("rmi://localhost/");
        while(e.hasMoreElements()) {
            System.out.println(e.nextElement().getName());
        }
        String url = "rmi://localhost/central_warehouse";
        Warehouse centralWarehouse = (Warehouse)namingContext.lookup(url);
        String desc = "Blackwell Toaster";
        double price = centralWarehouse.getPrice(desc);
        System.out.println(desc + ": " + price);
    }
}
