#include "LiftOff.h"
#include <iostream>
#include <zthread/ThreadedExecutor.h>
using namespace std;
using namespace ZThread;

int main() {
	try {
		ThreadedExecutor executor;
		for(int i = 0; i < 5; i++)
		  executor.execute(new LiftOff(10, i));
	} catch(Synchronization_Exception &e) {
		cerr << e.what() << endl;
	}	
	return 0;
}
