import java.lang.System;


public class Test {
    
    public static void main(String[] args) {
        String aString = "    ";
        System.out.println(aString.length());
        System.out.println(aString);
        
        String bString = aString.trim();
        System.out.println(bString.length());
        System.out.println(bString);
    }
}
