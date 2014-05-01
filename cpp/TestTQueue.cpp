#include "TQueue.h"
#include "LiftOff.h"
#include <string>
#include <iostream>
#include <zthread/Thread.h>

using namespace ZThread;
using namespace std;

class LiftOffRunner : public Runnable {
	TQueue<LiftOff*> rockets;
public:
	void add(LiftOff *lo) { rockets.put(lo); }
	void run() {
		try {
			while(!Thread::interrupted()) {
				LiftOff *rocket = rockets.get();
				rocket->run();
			}
		} catch(Interrupted_Exception &) {}
		cout << "Exiting LiftOffRunner " << endl;
	}
};

int main() {
	try {
		LiftOffRunner *lor = new LiftOffRunner;
		Thread t(lor);
		for(int i = 0; i < 5; i++) 
		  lor->add(new LiftOff(10, i));
		cin.get();
		lor->add(new LiftOff(10, 99));
		t.interrupt();
	} catch(Synchronization_Exception &e) {
		cerr << e.what() << endl;
	}
}

