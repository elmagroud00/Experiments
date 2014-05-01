#include <iostream>
#include <pthread.h>

using namespace std;

int Count = 0;

void *threadA(void *X) {
	Count += 2;
	cout << Count << endl;
}

void *threadB(void *X) {
	Count += 4;
	cout << Count << endl;
}

int main(void) {
	pthread_t ThreadA;
	pthread_t ThreadB;
	
	pthread_create(&ThreadA, NULL, threadA, NULL);
	pthread_create(&ThreadB, NULL, threadB, NULL);

	pthread_join(ThreadA, NULL);
	pthread_join(ThreadB, NULL);
}
