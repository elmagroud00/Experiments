import java.util.*;

public class Dotthis{
    void f() { System.out.println("Dotthis.f()"); }
    public class Inner{
        public Dotthis outer(){
            return Dotthis.this;
        }
    }
    public Inner inner() { return new Inner(); }
    public static void main(String[] args){
        Dotthis dt = new Dotthis();
        Dotthis.Inner dti = dt.inner();
        dti.outer().f();
    }
}
