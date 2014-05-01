import java.io.*;
import java.util.*;

public class ObjectSaver {

	public static void main(String args[]) throws Exception {
		try {
			ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream("/tmp/a.txt"));
			
			String obj1 = "hello";
			Date obj2 = new Date();
//		Customer obj3 = new Customer("Tom", 20);
			
			out.writeObject(obj1);
			out.writeObject(obj2);
//	out.writeObject(obj3);
			
			out.close();
			
			ObjectInputStream in = new ObjectInputStream(new FileInputStream("/tmp/a.txt"));
			String obj11 = (String)in.readObject();
			System.out.println("obj11: " + obj1);
			System.out.println("obj11 == obj1: " + (obj11 == obj1));
			System.out.println("obj11.equals(obk1): " + (obj11.equals(obj1)));
			
			in.close();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
}
