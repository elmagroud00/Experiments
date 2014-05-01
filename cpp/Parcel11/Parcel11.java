import java.util.*;

interface Contents{
    public int value();
}

interface Destination{
    public String readLabel();
}

public class Parcel11{
    private static class ParcelContent implements Contents{
        private int i = 11;
        public int value() { return i; }
    }
    protected static class ParcelDestination implements Destination{
        private String label;
        private ParcelDestination(String whereTo){
            label = whereTo;
        }
        public String readLabel() { return label; }
   
        //Nested classes can contain other static elementd;
        public static void f() {}
        static int x = 10;
        static class AnotherLevel{
            public static void f() {}
            static int x = 10;
        }
    }
    public static Destination destination(String s){
        return new ParcelDestination(s);
    }
    public static Contents contents(){
        return new ParcelContent();
    }
    public static void main(String[] args){
        Contents c = contents();
        Destination d = destination("Beijing");
    }
}///:~
