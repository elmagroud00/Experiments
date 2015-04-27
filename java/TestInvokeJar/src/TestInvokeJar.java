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
        cmd.add("sh");
        cmd.add("-c");
        cmd.add("rm -vrf /tmp/system_*");

        ProcessBuilder pb = new ProcessBuilder(cmd);
        pb.redirectErrorStream(true);

        try {
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
