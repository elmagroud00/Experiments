import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Semaphore;


public class SemaphoreExample {
	
	public static void main(String[] args) {
		ExecutorService pool = Executors.newCachedThreadPool();
		final Semaphore sem = new Semaphore(3);
		
		for(int i = 0; i < 10; i++) {
			Runnable runnable = new Runnable() {
				
				@Override
				public void run() {
					try {
						sem.acquire();
						System.out.println("Thread: " + Thread.currentThread().toString() + "running ...");
						Thread.sleep((long)(Math.random() * 1000));
						System.out.println("Thread: " + Thread.currentThread().toString() + "done");
						sem.release();
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			};
			pool.execute(runnable);
		}
		pool.shutdown();
	}
}
