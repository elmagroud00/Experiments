import java.util.*;

public interface ClassInInterface{
    void howdy();
    class Test implements ClassInInterface{
        public void howdy(){
            System.out.println("howdy!");
        }
        public static void main(String[] args){
            Test t = new Test();
            t.howdy();
        }
    }   
}
