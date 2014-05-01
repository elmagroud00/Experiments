import java.io.*;

public class Hex {
	public static String format(byte[] data){
		StringBuilder result = new StringBuilder();
		int n = 0;
		for(byte b : data){
			if(n % 16 == 0)
				result.append(String.format("%05x: ", n));
			result.append(String.format("%02x ", b));
			n++;
			if(n % 16 == 0)
				result.append("\n");
		}
		result.append("\n");
		return result.toString();
	}
	public static void main(String[] args){
		int r = (16 % 16);
		System.out.println(r);
	}
	
}
