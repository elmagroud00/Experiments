import java.util.*;

public class Parcel5{
    public Destination destionation(String s){
        class PDestination implements Destination{
            private String label;
            private PDestination(String whereTo){
                label = whereTo;
            }
            public String readLabel() { return whereTo; }
        }
        return new PDestination(s);
    }
}
