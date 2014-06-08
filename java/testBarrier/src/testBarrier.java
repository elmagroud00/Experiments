import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;


public class testBarrier {
	public static void main(String[] args) {
		ExecutorService service = Executors.newCachedThreadPool();
		final Cyrrier cb = new CyclicBarrier(3);
		
		for(int  i = 0; i < 3; i++) {
			Runnable runnable = new Runnable() {
				
				@Override
				public void run() {
					try {
						Thread.sleep((long)Math.random() * 100000);
						System.out.println("Thread: " + Thread.currentThread().toString() 
								+ "There are have: " + (cb.getNumberWaiting() + 1) 
								+ (cb.getNumberWaiting() == 2 ? "go on" : "wait"));
						cb.await();
						Thread.sleep((long)Math.random() * 100000);
						System.out.println("Thread: " + Thread.currentThread().toString() + "There are have: " + (cb.getNumberWaiting() + 1));
						cb.await();
					} catch(Exception e) {
						e.printStackTrace();
					}
				}
			};
			service.execute(runnable);
		}
		service.shutdown();
	}
}
