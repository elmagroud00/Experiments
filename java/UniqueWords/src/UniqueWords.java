import java.util.*;

public class UniqueWords {
	public static void main(String[] args){
		Set<String> words = new TreeSet<String>(
				new TextFile("UniqueWords.java", "\\w+"));
		System.out.println(words);
	}
}
