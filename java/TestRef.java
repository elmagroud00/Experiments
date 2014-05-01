import java.io.*;

public class TestRef {
    static { System.loadLibrary("TestRefJNI"); }

    public static native int getMethod();

    public static void main(String[] args) {
        Test.setNum(1);
        System.out.println("Num = " + getMethod());
        Test.setNum(2);
        System.out.println("Num = " + getMethod());
    }
}

class Test {
    public static int m_num;

    public static void setNum(int num) {
        m_num = num;
    }
}
