#include <iostream>
#include <zthread/Thread.h>
using namespace ZThread;
using namespace std;

const double PI = 3.141592634234234234234234234;
const double E = 2.73242423423423432432;

class NeedsCleanup {
	int id;
public:
	NeedsCleanup(int ident) : id(ident) {
		cout << "NeedCleanup " << id << endl;
	}
	~NeedsCleanup() {
		cout << "~NeedCleanup " << id << endl;
	}
};

class Blocked3 : public Runnable {
	volatile double d;
public:
	Blocked3() : d(0.0) {}
	void run() {
		try {
			while(!Thread::interrupted()) {
				point1:
				NeedsCleanup n1(1);
				cout << "Sleeping " << endl;
				Thread::sleep(1000);
				point2:
				NeedsCleanup n2(2);
				cout << "Calculating " << endl;
				// A time-consuming, non-blocking operator:
				for(int i = 0; i < 10000; i++)
				  d = d + (PI + E) / (double)i;
			}
			cout << "Exiting via while() test" << endl;
		} catch(Interrupted_Exception &e) {
			cout << "Exiting via Interrupted_Exception" << endl;
		}
	}
};

int main(int argc, char **argv) {
	if(argc != 2) {
		cerr << "usage: " << argv[0]
			<< " delay-in-milliseconds" << endl;
		exit(1);
	}
	int delay = atoi(argv[1]);
	try {
		Thread t(new Blocked3);
		Thread::sleep(delay);
		t.interrupt();
	} catch(Synchronization_Exception &e) {
		cerr << e.what() << endl;
	}
}
