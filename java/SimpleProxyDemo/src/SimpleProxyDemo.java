
interface Interface{
	void doSomething();
	void somethingElse(String arg);
}

class RealObject implements Interface{
	public void doSomething() {System.out.println("doSomething");}
	public void somethingElse(String arg){
		System.out.println("SomethingElse " + arg);
	}
}

class SimpleProxy implements Interface{
	private Interface proxied;
	public SimpleProxy(Interface proxyed){
		this.proxied = proxyed;
	}
	public void doSomething(){
		System.out.println("SimpleProxy doSomeThing");
		proxied.doSomething();
	}
	public void somethingElse(String arg){
		System.out.println("SimpleProxy sonethingElse " + arg);
		proxied.somethingElse(arg);
	}
}

public class SimpleProxyDemo {
	public static void consumer(Interface ifac){
		ifac.doSomething();
		ifac.somethingElse("bonoobo");
	}
	public static void main(String[] args){
		consumer(new RealObject());
		consumer(new SimpleProxy(new RealObject()));
	}
}

