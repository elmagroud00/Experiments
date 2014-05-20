#include "thread.h"
#include <iostream>
using namespace std;

void *Thread::run0(void *args)
{
	Thread *p = (Thread*)args;
	p->run1();
	return p;
}

void *Thread::run1()
{
	threadStatus = THREAD_STATUS_RUNNING;
	tid = pthread_self();
	run();
	threadStatus = THREAD_STATUS_EXIT;
	tid = 0;
	pthread_exit(NULL);
}

Thread::Thread()
{
	tid = 0;
	threadStatus = THREAD_STATUS_NEW;
}

bool Thread::start()
{
	return pthread_create(&tid, NULL, run0, this) == 0;
}

pthread_t Thread::getThreadID()
{
	return tid;
}

int Thread::getStatus()
{
	return threadStatus;
}

void Thread::join()
{
	if(tid > 0)
		pthread_join(tid, NULL);
}

void Thread::join(unsigned long millisTime)
{
	if(tid == 0)
		return;
	if(millisTime == 0)
		join();
	else
	{
		unsigned long k = 0;
		while(threadStatus != THREAD_STATUS_EXIT && k <= millisTime)
		{
			usleep(100);
			k++;
		}
	}
}

void MutiThread::run() 
{
	int number = 0;
	for(int i = 0; i < 10; i++)
	{
		cout << "Currrent number is " << number++;
		cout << "PID is " << getpid() << "TID is " << getThreadID() << endl;
		sleep(1);
	}
}
