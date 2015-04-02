import java.io.File;
import java.io.IOException;

public class TestSymlnk {

    public static void main(String[] args) {
        System.out.println(String.valueOf(false));
        
        System.out.println(System.currentTimeMillis());

        File dir = new File("/tmp/testsym");
        File files[] = dir.listFiles();

        for (int i = 0; i < files.length; i++) {
            File file = files[i];
            System.out.println("Abs:" + file.getAbsolutePath());
            System.out.println("parent: " + file.getParent());
            System.out.println("parent file: " + file.getParentFile());

            try {
                System.out.println("Can: " + file.getCanonicalPath());
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }

    }
}
