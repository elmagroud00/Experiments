import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;


public class CyclicBarrierExample {
	
	public static void main(String[] args) {
		ExecutorService pool = Executors.newCachedThreadPool();
		final CyclicBarrier barrier = new CyclicBarrier(5);
		
		for(int i = 0; i < 5; i++) {
			Runnable runnable = new Runnable() {
				
				@Override
				public void run() {
					try {
						Thread.sleep((long)(Math.random() * 1000));
						System.out.println("Thread: " + Thread.currentThread().toString() + "step 1 done. "
								+ (barrier.getNumberWaiting() +1) + " thread finished!");
						
						barrier.await();
						System.out.println("Thread: " + Thread.currentThread().toString() + "start step 2 ...");
						
					} catch(InterruptedException e) {
						e.printStackTrace();
					} catch(BrokenBarrierException e) {
						e.printStackTrace();
					}
				}
			};
			pool.execute(runnable);
		}
		pool.shutdown();
	}
}
