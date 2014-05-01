#include <iostream>
#include <zthread/Thread.h>
#include <zthread/ThreadedExecutor.h>
using namespace std;
using namespace ZThread;

class Count {
	enum { SZ = 100 };
	int n[SZ];
public:
	void increment() {
		for(int i = 0; i < SZ; i++) {
		  n[i]++;
		  cout << n[i];
		}
	}
};

class Incrementer : public Runnable {
	Count *count;
public:
	Incrementer(Count *c) : count(c) {}
	void run() {
		for(int n = 100; n > 0; n--) {
			Thread::sleep(250);
			count->increment();
		}
	}
};

int main() {
	cout << "This will cause a segmentation fault!" << endl;
	Count count;
	try {
		Thread t0(new Incrementer(&count));
		Thread t1(new Incrementer(&count));
	} catch(Synchronization_Exception &e) {
		cerr << e.what() << endl;
	}
	getchar();
}
