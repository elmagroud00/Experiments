import java.io.*;

public class InputFile {
	private BufferedReader in;
	public InputFile(String fname) throws Exception{
		try{
			in = new BufferedReader(new FileReader(fname));
			//Other code that might throws exceptions
		}catch(FileNotFoundException e){
			System.out.println("Could not open " + fname);
			//Was not open. so do not close it
			throw e;
		}catch(Exception e){
			//All other exceptions must close it
			try{
				in.close();
			}catch(IOException e2){
				System.out.println("in.close() unsuccessful");
			}
			throw e;
		}finally{
			//Do not close it here!!!
		}
	}
	public String getLine(){
		String s;
		try{
			s = in.readLine();
		}catch(IOException e){
			throw new RuntimeException("readline() failed");
		}
		return s;
	}
	public void dispose(){
		try{
			in.close();
			System.out.println("dispose() successful");
		}catch(IOException e2){
			throw new RuntimeException("in.close() failed");
		}
	}
	public static void main(String[] args){
		try{
			InputFile IF = new InputFile("/tmp/a.txt");
			while(IF.getLine() != null)
				System.out.println(IF.getLine());
			IF.dispose();
		}catch(Exception e){
			System.out.println("Exception main");
		}
		
		
	}
}
