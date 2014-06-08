#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>
#include <unistd.h>

class Thread
{
private:
	pthread_t	tid;
	int	threadStatus;
    static void *run0(void *args);
	void *run1();
public:
	static const int THREAD_STATUS_RUNNING = 1;
	static const int THREAD_STATUS_EXIT = -1;
	
	Thread();
	virtual ~Thread();
	virtual void run() = 0;
	bool start();
	int getStatus();
	void exitThread();
	void join();
	void join(unsigned long millisTime);	
	pthread_t	getThreadID();
};
#endif

