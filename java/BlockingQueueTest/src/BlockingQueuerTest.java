import java.io.*;
import java.util.*;
import java.util.concurrent.*;

public class BlockingQueuerTest {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		System.out.print("Enter base directory: ");
		String directory = in.nextLine();
		System.out.print("Enter keyword: ");
		String keyword = in.nextLine();
		
		final int FILE_QUEUE_SIZE = 10;
		final int SEARCH_THREADS = 100;
		
		BlockingQueue<File> queue = new ArrayBlockingQueue<File>(FILE_QUEUE_SIZE);
		
		FileEnumerationTask enumerator = new FileEnumerationTask(queue, new File(directory));
		new Thread(enumerator).start();
		for(int i = 1; i <= SEARCH_THREADS; i++) {
			new Thread(new SearchTask(queue, keyword)).start();
		}
	}
}

class FileEnumerationTask implements Runnable {
	
	private BlockingQueue<File> queue;
	private File startingDirectory;
	public static File DUMMY = new File("");
	
	public FileEnumerationTask(BlockingQueue<File> queue, File startingDirectory) {
		this.queue = queue;
		this.startingDirectory = startingDirectory;
	}
	
	public void enumerate(File directory) throws InterruptedException {
		File[] files = directory.listFiles();
		for(File file : files) {
			System.out.println(file.toString());
			if(file.isDirectory())
				enumerate(file);
			else
				queue.put(file);
		}
	}
	
	public void run() {
		try {
			enumerate(startingDirectory);
			queue.put(DUMMY);
		} catch(InterruptedException e) {
			
		}
	}
}

class SearchTask implements Runnable {
	
	private BlockingQueue<File> queue;
	private String keyword;
	
	public SearchTask(BlockingQueue<File> queue, String keyword) {
		this.queue = queue;
		this.keyword = keyword;
	}
	
	public void run() {
		try {
			boolean done = false;
			while(!done) {
				File file = queue.take();
				if(file == FileEnumerationTask.DUMMY) {
					queue.put(file);
					done = true;
				} else 
					search(file);
			}
		} catch(IOException e) {
			e.printStackTrace();
		} catch(InterruptedException e) {
			e.printStackTrace();
		}
	}
	
	/* Searchs a file for a given keyword and prints all matching lines */
	public void search(File file) throws IOException {
		Scanner in = new Scanner(new FileInputStream(file));
		int lineNumber = 0;
		
		while(in.hasNext()) {
			lineNumber++;
			String line = in.nextLine();
			if(line.contains(keyword)) 
				System.out.printf("%s:%d:%s%n", file.getPath(), lineNumber, line);
		}
		in.close();
	}
}




































