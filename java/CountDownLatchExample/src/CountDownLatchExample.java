import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;


public class CountDownLatchExample {
	
	public static void main(String[] args) {
		ExecutorService pool = Executors.newCachedThreadPool();
		final CountDownLatch doneLatch = new CountDownLatch(10);
		
		for(int i = 0; i < 10; i++) {
			Runnable runnable = new Runnable() {
				
				@Override
				public void run() {
					try {
						Thread.sleep((long)(Math.random() * 1000));
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
					System.out.println("Thread: " + Thread.currentThread().toString() + " done");
					doneLatch.countDown();
				}
			};
			pool.execute(runnable);
		}
		try {
			doneLatch.await();
			System.out.println("All Thread Done!");
		} catch(InterruptedException e) {
			e.printStackTrace();
		}
		pool.shutdown();
	}
}
