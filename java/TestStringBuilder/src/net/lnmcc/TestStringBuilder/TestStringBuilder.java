package net.lnmcc.TestStringBuilder;

public class TestStringBuilder {
    public static void main(String[] args) {
        StringBuffer sb = new StringBuffer();
        System.out.println(sb.toString());
        
        String str1 = "";
        String str2 = "a\n";
        
        System.out.println(str1 + str2);
    }
}
