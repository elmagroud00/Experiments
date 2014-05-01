#include "EventChecker.h"
#include <iostream>
#include <zthread/ThreadedExecutor.h>
using namespace std;
using namespace ZThread;

class EventGenerator : public Generator {
	unsigned int currentEventValue;
public:
	EventGenerator() { currentEventValue = 0; }
	~EventGenerator() { cout << "~EventGenerator" << endl; }
	int nextValue() {
		++currentEventValue;
		++currentEventValue;
		return currentEventValue;
	}
};

int main() {
	EventChecker::test<EventGenerator>();
}
