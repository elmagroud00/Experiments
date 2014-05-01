#include "EventChecker.h"
#include <iostream>
#include <zthread/Mutex.h>
#include <zthread/Guard.h>
using namespace std;
using namespace ZThread;

class GuardedEventGenerator : public Generator {
	unsigned int currentEventValue;
	Mutex lock;
public:
	GuardedEventGenerator() { currentEventValue = 0; }
	~GuardedEventGenerator() {
		cout << "~GuardedEventGenerator" << endl;
	}
	int nextValue() {
		Guard<Mutex> g(lock);
		++currentEventValue;
		Thread::yield();
		++currentEventValue;
		return currentEventValue;
	}
};

int main() {
	EventChecker::test<GuardedEventGenerator>();
}
