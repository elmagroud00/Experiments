import java.util.*;

class MNA{
    private void f() {}
    class A{
        private void g() {}
        public class B{
            void h(){
                g();
                f();
            }
        }
    }
}

public class MutilNestingAccess{
    public static void main(String[] args){
        MNA mna = new MNA();
        MNA.A mnaa = mna.new A();
        MNA.A.B mmaab = mnaa.new B();
        mmaab.h();
    }
}
