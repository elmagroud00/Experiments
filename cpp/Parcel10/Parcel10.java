import java.util.*;

interface Destination{
    public String readLabel();
}

public class Parcel10{
    public Destination destination(final String dest, final float price){
        return new Destination(){
            private int cost;
            //Instance initialion for each object:
            {
                cost = Math.round(price);
                if(cost > 100)
                    System.out.println("Over budget!");
            }
            private String label = dest;
            public String readLabel() { return label; }
        };
    }
    public static void main(String[] args){
        Parcel10 p = new Parcel10();
        Destination d = p.destination("Beijing", 1000F);
    }
}
