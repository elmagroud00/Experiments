import java.io.*;
import java.util.*;
import java.util.concurrent.*;

public class ThreadPoolTest {
	
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		System.out.println("Enter base directory");
		String directory = in.nextLine();
		System.out.println("Enter keyword");
		String keyword = in.nextLine();
		
		ExecutorService pool = Executors.newCachedThreadPool();
		
		MatchCounter counter = new MatchCounter(new File(directory), keyword, pool);
		Future<Integer> result = pool.submit(counter);
		
		try {
			System.out.println(result.get() + "matched files");
		} catch(ExecutionException e) {
			e.printStackTrace();
		} catch(InterruptedException e) {
			e.printStackTrace();
		}
		
		pool.shutdown();
		
		int largestPoolSize = ((ThreadPoolExecutor)pool).getLargestPoolSize();
		System.out.println("Largest pool size = " + largestPoolSize);
	}
}
