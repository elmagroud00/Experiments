/* ************************************************************************
  > File Name: MyRemoteImpl.java
  > Author: lnmcc
  > Mail: lnmcc@hotmail.com 
  > Blog: lnmcc.net 
  > Created Time: Wed Apr  9 00:08:27 2014
 *********************************************************************** */
import java.rmi.*;
import java.rmi.server.*;

public class MyRemoteImpl extends UnicastRemoteObject implements MyRemote {

    public String sayHello() {
        return "Server say hello";
    }

    public MyRemoteImpl() throws RemoteException {

    }

    public static void main(String[] args) {
        try {
            MyRemote service = new MyRemoteImpl();
            Naming.rebind("RemoteHello", service);
        } catch(Exception e) {
            e.printStackTrace();
        }
    }
}


