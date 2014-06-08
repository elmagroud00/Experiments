import java.io.*;
import java.util.*;
import java.util.concurrent.*;

public class MatchCounter implements Callable<Integer> {
	
	private File directory;
	private String keyword;
	private ExecutorService pool;
	private int count;;
	
	public MatchCounter(File directory, String keyword, ExecutorService pool) {
		this.directory = directory;
		this.keyword = keyword;
		this.pool = pool;
	}
	
	public Integer call() {
		count = 0;
		
		try {
			File[] files = directory.listFiles();
			ArrayList<Future<Integer> > results = new ArrayList<Future<Integer> >();
			
			for(File file : files) {
				if(file.isDirectory()) {
					MatchCounter counter = new MatchCounter(file, keyword, pool);
					Future<Integer> result = pool.submit(counter);
					results.add(result);
				} else {
					if(search(file))
						count++;
				}
			}
			for(Future<Integer> result : results) {
				try {
					count += result.get();
				} catch(ExecutionException e) {
					e.printStackTrace();
				}
			}
		} catch(InterruptedException e) {
			e.printStackTrace();
		}
		return count;
	}
	
	public boolean search(File file) {
		try {
			Scanner in = new Scanner(new FileInputStream(file));
			boolean found = false;
			while(!found && in.hasNext()) {
				String line = in.nextLine();
				if(line.contains(keyword))
					found = true;
			}
			in.close();
			return found;
		} catch(IOException e) {
			e.printStackTrace();
			return false;
		}
	}
}






















