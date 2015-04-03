import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class TestInvokeJar {

    public static void main(String[] args) {
        System.out.println(System.currentTimeMillis());

        ArrayList<String> cmd = new ArrayList<String>();
        cmd.add("java");
        cmd.add("-Xmx2048m");
        cmd.add("-jar");
        cmd.add("/home/sijiewang/Desktop/signapk.jar");
        cmd.add("-w");
        cmd.add("/home/sijiewang/Projects/8916-tools/LINUX/android/build/target/product/security/testkey.x509.pem");
        cmd.add("/home/sijiewang/Projects/8916-tools/LINUX/android/build/target/product/security/testkey.pk8");
        cmd.add("/home/sijiewang/tmp/ota/full_update.zip");
        cmd.add("/home/sijiewang/tmp/ota/full_update-sign.zip");

        ProcessBuilder pb = new ProcessBuilder(cmd);
        pb.redirectErrorStream(true);

        try {
            // Process process = Runtime.getRuntime().exec(
            // "java  -Xmx2048m -jar /home/sijiewang/Desktop/signapk.jar");
            Process process = pb.start();

            InputStream is = process.getInputStream();
            BufferedReader read = new BufferedReader(new InputStreamReader(is));
            String line;
            while ((line = read.readLine()) != null) {
                System.out.println(line);
            }

        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        System.out.println(System.currentTimeMillis());
    }

}
