public class Test {
    public static void main(String[] args) {
        System.out.println("This is a thrower Test");
        Test t = new Test();
        try {
            t.test();
        } catch (IllegalAccessError e) {
            e.printStackTrace();
        }
        System.out.println("Test finished");
    }

    public void test() {
        throw new IllegalAccessError();
    }
}
