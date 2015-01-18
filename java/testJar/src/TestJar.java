import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.jar.JarEntry;
import java.util.jar.JarInputStream;
import java.util.jar.JarOutputStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

public class TestJar {

	/**
	 * @param src
	 *            : files you want to add to the jar file
	 * @param dst
	 */
	public static void GenerateJar(String[] src, String dst) {
		try {
			ZipOutputStream out = new ZipOutputStream(new FileOutputStream(dst));
			byte[] buf = new byte[1024];

			// Compress each file
			for (int i = 0; i < src.length; i++) {
				String file = src[i];
				System.out.print("Process file: " + file);

				FileInputStream in = new FileInputStream(file);
				out.putNextEntry(new ZipEntry(file));

				int len;
				while ((len = in.read(buf)) > 0) {
					out.write(buf, 0, len);
				}
				out.closeEntry();
				in.close();
			}
			out.close();
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}

	public static void main(String[] args) {
		System.out.println("Begin ..." + System.currentTimeMillis());

		String[] src = {
				"./ACDC.wav",
				"./acdc.xls"
		};
		String dst = "/tmp/test.jar";

		GenerateJar(src, dst);

		System.out.println("End " + System.currentTimeMillis());
	}
}
