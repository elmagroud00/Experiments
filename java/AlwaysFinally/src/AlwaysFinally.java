import java.util.*;

class FourException extends Exception {}

public class AlwaysFinally {
	public static void main(String[] args){
		System.out.println("In main");
		try{
			System.out.println("Entrying first try block");
			//throw new FourException();
		}catch(NullPointerException e){
			System.out.println("caught!");
		}finally{
			System.out.println("finally block");
		}
	}
}
