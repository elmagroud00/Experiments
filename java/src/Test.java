import java.util.Random;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Test {

	public static void main(String[] args) {
		System.out.println("Begin ..." + System.currentTimeMillis());
		ExecutorService executor = Executors.newFixedThreadPool(5);
		CyclicBarrier barrier = new CyclicBarrier(5);
		executor.execute(new Runner(barrier, "a"));
		executor.execute(new Runner(barrier, "b"));
		executor.execute(new Runner(barrier, "c"));
		executor.execute(new Runner(barrier, "d"));
		executor.execute(new Runner(barrier, "e"));

		try {
			Thread.sleep(1000 * 15);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		executor.execute(new Runner(barrier, "1"));
		executor.execute(new Runner(barrier, "2"));
		executor.execute(new Runner(barrier, "3"));
		executor.execute(new Runner(barrier, "4"));
		executor.execute(new Runner(barrier, "5"));

		executor.shutdown();
	}
}

class Runner implements Runnable {

	private String mName;
	private CyclicBarrier mBarrier;

	public Runner(CyclicBarrier barrier, String name) {
		mName = name;
		mBarrier = barrier;
	}

	@Override
	public void run() {
		System.out.println("I am running: " + mName);
		try {
			Thread.sleep(1000 * ((new Random()).nextInt(10)));
			mBarrier.await();
			System.out.println(mName + " done");
		} catch (InterruptedException e) {
			e.printStackTrace();
		} catch (BrokenBarrierException e) {
			e.printStackTrace();
		}
	}
}