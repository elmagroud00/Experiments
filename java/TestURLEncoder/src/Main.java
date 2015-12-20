import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;
import java.net.URLEncoder;


public class Main {
	
	public static void main(String[] args) {
		System.out.println(System.currentTimeMillis());
		
		String url = "name=瓦罐&sex=1";
		System.out.println("Ori url: " + url);
		
		try {
			String url2 = URLEncoder.encode(url, "UTF-8");
			System.out.println("url2: " + url2);
			String url3 = URLEncoder.encode(url2, "UTF-8");
			System.out.println("url3: " + url3);
			
			String dUrl1 = URLDecoder.decode(url2, "UTF-8");
			System.out.println("dUrl1: " + dUrl1);
			
			String dUrl2 = URLDecoder.decode(url3);
			System.out.println("dUrl2: " + dUrl2);
			
			//String url3 = URLEncoder.encode(url)
			
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
}
