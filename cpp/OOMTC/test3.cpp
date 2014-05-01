#include <iostream>
#include <cstdlib>
#include <pthread.h>
using namespace std;

class A {
public:
	A() : i(0) { cout << "Constructor" << endl; }
	~A() { cout << "Deconstructor" << endl; }
	void run() {
		while(1) {
		cout << i << endl;
		i++;
		if(i == 100000) 
			//exit(1);
			return;
		}
	}
private:
	int i;
};

void *func(void *X) {
	A *a = static_cast<A*>(X);
	a->run();
}

int main() {
	A a;
	pthread_t pid;
	if(pthread_create(&pid, NULL, func, (void*)&a)) {
		cout << "Can not create thread" << endl;
		exit(1);
	}
	int i = 0;
	pthread_join(pid, NULL);	
	cout << "End" << endl;
}
