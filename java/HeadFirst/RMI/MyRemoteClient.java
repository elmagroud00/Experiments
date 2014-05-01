/* ************************************************************************
  > File Name: MyRemoteClient.java
  > Author: lnmcc
  > Mail: lnmcc@hotmail.com 
  > Blog: lnmcc.net 
  > Created Time: Wed Apr  9 00:18:07 2014
 *********************************************************************** */
import java.rmi.*;

public class MyRemoteClient {
    
    public static void main(String[] args) {
        new MyRemoteClient().go();
    }

    public void go() {
        try {
            MyRemote service = (MyRemote)Naming.lookup("rmi://127.0.0.1/RemoteHello");
            String s = service.sayHello();
            System.out.println(s);
        } catch(Exception e) {
            e.printStackTrace();
        }
    }
}
