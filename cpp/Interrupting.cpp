#include <iostream>
#include <zthread/Thread.h>
using namespace std;
using namespace ZThread;

class Blocked : public Runnable {
public:
	void run() {
		try {
			Thread::sleep(1000);
			cout << "Waiting for get() in run(): ";
			cin.get();
		} catch(Interrupted_Exception &e) {
			cout << "Caught Interrupted_Exception" << endl;
		}
	}
};

int main(int argc, char **argv) {
	try {
		Thread t(new Blocked);
		if(argc > 1)
		  Thread::sleep(1100);
		t.interrupt();
	} catch(Synchronization_Exception &e) {
		cerr << e.what() << endl;
	}
}
