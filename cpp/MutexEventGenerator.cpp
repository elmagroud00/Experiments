#include "EventChecker.h"
#include <iostream>
#include <zthread/ThreadedExecutor.h>
#include <zthread/Mutex.h>
using namespace ZThread;
using namespace std;

class MutexEventGenerator : public Generator {
	unsigned int currentEventValue;
	Mutex lock;
public:
	MutexEventGenerator() { currentEventValue = 0; }
	~MutexEventGenerator() {
		cout << "~MutexEventGenerator" << endl;
	}
	int nextValue() {
		lock.acquire();
		++currentEventValue;
		Thread::yield();
		++currentEventValue;
		int rval = currentEventValue;
		lock.release();
		return rval;
	}
};

int main() {
	EventChecker::test<MutexEventGenerator>();
}
