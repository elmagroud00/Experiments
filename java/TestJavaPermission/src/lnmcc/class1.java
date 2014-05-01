package lnmcc;

public class class1 {
	String s = "hello world";
	
	public class1() {
		System.out.println("This is constructor of class1:" + " s = " + s);
	}
	
	public static void main(String args[]) {
		@SuppressWarnings("unused")
		class2 b = new class2();
	}
}

class class2 {	
	class1 a = new class1();
	public class2() {
		System.out.println("This is constructor of class2: " + "s = " + a.s);
	}
}


