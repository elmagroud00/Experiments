#include "Thread.h"
#include <iostream>
using namespace std;

Thread::Thread() {
	tid = 0;
}

Thread::~Thread() {

}

void *Thread::run0(void *args) {
	Thread *p = (Thread*)args;
	p->run1();
	return p;
}

void *Thread::run1() {
	threadStatus = THREAD_STATUS_RUNNING;
	tid = pthread_self();
	run();
	threadStatus = THREAD_STATUS_EXIT;
	tid = 0;
	pthread_exit(NULL);
	return 0;
}

void Thread::exitThread() {

}

bool Thread::start() {
	return pthread_create(&tid, NULL, run0, this) == 0;
}

pthread_t Thread::getThreadID() {
	return tid;
}

int Thread::getStatus() {
	return threadStatus;
}

void Thread::join() {
	if(tid > 0)
		pthread_join(tid, NULL);
}

void Thread::join(unsigned long millisTime) {
	if(tid == 0)
		return;
	if(millisTime == 0)
		join();
	else {
		unsigned long k = 0;
		while(threadStatus != THREAD_STATUS_EXIT && k <= millisTime) {
			usleep(100);
			k++;
		}
	}
}

