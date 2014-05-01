/* ************************************************************************
  > File Name: MyRemote.java
  > Author: lnmcc
  > Mail: lnmcc@hotmail.com 
  > Blog: lnmcc.net 
  > Created Time: Wed Apr  9 00:06:05 2014
 *********************************************************************** */
import java.rmi.*;

public interface MyRemote extends Remote {
    public String sayHello() throws RemoteException;
}
