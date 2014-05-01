/* ************************************************************************
  > File Name: HelloJNI.java
  > Author: lnmcc
  > Mail: lnmcc@hotmail.com 
  > Blog: lnmcc.net 
  > Created Time: Mon Apr  7 13:30:23 2014
 *********************************************************************** */
import java.io.*; 

class HelloJNI {
    native void printHello();
    native void printString(String str);

    static {
        System.loadLibrary("hellojni");
    }

    public static void main(String[] args) {
        HelloJNI myJNI = new HelloJNI();
        myJNI.printHello();
        myJNI.printString("Hello World from printString func");
    }
}
