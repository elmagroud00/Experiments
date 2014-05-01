package ToyTest;

interface HasBatteries {}
interface Waterproof {}
interface Shoots {}

class Toy{
	Toy() {}
	Toy(int i) {}
}

class FancyToy extends Toy implements HasBatteries, Waterproof, Shoots{
	FancyToy() { super(1); }
	
}

public class ToyTest {
	static void printInfo(Class cc){
		System.out.println("Class name: " + cc.getName() + 
				"is interface?[" + cc.isInterface() + "]");
		System.out.println("Simple name: " + cc.getCanonicalName());
	}
	public static void main(String[] args){
		Class cc = null;
		try{
			cc = Class.forName("ToyTest.FancyToy");
		}catch(ClassNotFoundException e){
			System.out.println("Can not find ToyTest.FancyToy");
			System.exit(1);
		}
		printInfo(cc);
		for(Class face : cc.getInterfaces())
			printInfo(face);
		Class up = cc.getSuperclass();
		Object obj = null;
		try{
			obj = up.newInstance();
		}catch(InstantiationException e){
			System.out.println("Cannot instantiate");
			System.exit(1);
		}catch(IllegalAccessException e){
			System.out.println("Cannot access");
			System.exit(1);
		}
		System.out.println(obj.getClass());
	}
}
