#include "DiningPhilosophers.h"
#include <zthread/ThreadedExecutor.h>
#include <ctime>

using namespace std;
using namespace ZThread;

int main(int argc, char **argv) {
	srand(time(0));
	int ponder = argc > 2 ? atoi(argv[1]) : 5;
	cout << "Press <Enter> to quit" << endl;
	enum { SZ = 5 };
	try {
		CountedPtr<Display> d(new Display);
		ThreadedExecutor executor;
		Chopstick c[SZ];
		for(int i = 0; i < SZ; i++) {
			executor.execute(new Philosopher(c[i], c[(i + 1) % SZ], d, i, ponder));
		}
		cin.get();
		executor.interrupt();
		executor.wait();
	} catch(Synchronization_Exception &e) {
		cerr << e.what() << endl;
	}	
}
