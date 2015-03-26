import java.io.*;

public class Main {

    public static void main(String[] args) {

        String value = "true";
        System.out.println(String.valueOf(Boolean.valueOf(value)));
        
        try {

            byte[] sim = { (byte) 0xbc, (byte) 0xf2, // 简
                    (byte) 0xcc, (byte) 0xe5, // 体
                    (byte) 0xd6, (byte) 0xd0, // 中
                    (byte) 0xce, (byte) 0xc4 }; // 文
            InputStreamReader inputStreamReader = new InputStreamReader(
                    new ByteArrayInputStream(sim), "GB2312");
            PrintWriter printWriter = new PrintWriter(new OutputStreamWriter(
                    System.out, "GB2312"));
            PrintStream printStream = new PrintStream(System.out, true,
                    "GB2312");
            int in;
            while ((in = inputStreamReader.read()) != -1) {

                printWriter.println((char) in);

                printStream.println((char) in);

            }
            
            printWriter.println(new char[]{0xbc, 0xf2});

            inputStreamReader.close();
            printWriter.close();
            printStream.close();

        } catch (ArrayIndexOutOfBoundsException e) {

            e.printStackTrace();

        } catch (IOException e) {

            e.printStackTrace();

        }

    }

}