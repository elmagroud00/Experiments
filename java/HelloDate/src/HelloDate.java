//: object/HelloDate.java
import java.util.*;

/** The first Thinking in Java example program.
  * Displays a string and today's data.
  * @author lnmcc
  * @author www.lnmcc.net
  * @version 1.0
  */
public class HelloDate{
	public static void main(String [] args){
        /** Entry point to class & application.
          * @param args array of string arguments
          * @throws exceptions No exception thrown
          */
		System.out.println("Hello, it's: ");
		System.out.println(new Date());/* Output: (55% match)
                                          Hello, its's: 
                                          Wed Oct 05 14:39:36 MDT 2005
                                          *///:~
	}
}
