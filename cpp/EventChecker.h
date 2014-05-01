#ifndef EVENTCHECKER_H
#define EVENTCHECKER_H

#include <iostream>
#include <zthread/CountedPtr.h>
#include <zthread/Thread.h>
#include <zthread/Cancelable.h>
#include <zthread/ThreadedExecutor.h>

class Generator : public ZThread::Cancelable {
	bool canceled;
public:
	Generator() : canceled(false) {}
	virtual int nextValue() = 0;
	void cancel() { canceled = true; }
	bool isCanceled() { return canceled; }
};

class EventChecker : public ZThread::Runnable {
	ZThread::CountedPtr<Generator> generator;
	int id;
public:
	EventChecker(ZThread::CountedPtr<Generator> &g, int ident) : generator(g), id(ident) {}
	~EventChecker() {
		std::cout << "~EventChecker " << id << std::endl;
	}
	void run() {
		while(!generator->isCanceled()) {
			int val = generator->nextValue();
			if(val % 2 != 0) {
				std::cout << val << " not even!" << std::endl;
				generator->cancel();
			}
		}
	}
	template<typename GenType> static void test(int n = 10) {
		std::cout << "Press Control-C to exit" << std::endl;
		try {
			ZThread::ThreadedExecutor executor;
			ZThread::CountedPtr<Generator> gp(new GenType);
			for(int i = 0; i < n; i++)
			  executor.execute(new EventChecker(gp, i));
		} catch(ZThread::Synchronization_Exception &e) {
			std::cerr << e.what() << std::endl;
		}
	}
};

#endif // EVENTCHECKER_H
