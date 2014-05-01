#include <iostream>
#include <zthread/Thread.h>
#include <zthread/Mutex.h>
#include <zthread/Guard.h>
using namespace ZThread;
using namespace std;

class BlockedMutex {
	Mutex lock;
public:
	BlockedMutex() {
		//lock.acquire();

	}
	void f() {
		Guard<Mutex> g(lock);
		// This will never be available
	}
};
class Block2 : public Runnable {
	BlockedMutex blocked;
public:
	void run() {
			try {
				while(1) {
				cout << "Waiting for f() in BlockedMutex" << endl;
				Thread::sleep(1000);
				}
				//blocked.f();
			} catch(Interrupted_Exception &e) {
				cerr << e.what() << endl;
				// Exit the task
			}
	}
};

int main(int argc, char **argv) {
	try {
		Thread t(new Block2);
//		t.interrupt();
	} catch(Synchronization_Exception &e) {
		cerr << e.what() << endl;
	}
}
