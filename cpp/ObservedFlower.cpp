#include "Observable.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Flower {
	bool isOpen;
public:
	Flower() : isOpen(false), openNotifier(this), closeNotifier(this) {}
	void open() {
		isOpen = true;
		openNotifier.notifyObservers();
		closeNotifier.open();
	}
	void close() {
		isOpen = false;
		closeNotifier.notifyObservers();
		openNotifier.close();
	}
	// Using the "inner class" idiom:
	class OpenNotifier;
	friend class Flower::OpenNotifier;
	class OpenNotifier : public Observable {
		Flower *parent;
		bool alreadyOpen;
	public:
		OpenNotifier(Flower *f) : parent(f), alreadyOpen(false) {}
		void notifyObservers(Argument *arg = 0) {
			if(parent->isOpen && !alreadyOpen) {
				setChanged();
				Observable::notifyObservers();
				alreadyOpen = true;
			}
		}
		void close() { alreadyOpen = false; } 
	} openNotifier;

	class CloseNotifier;
	friend class Flower::CloseNotifier;
	class CloseNotifier : public Observable {
		Flower *parent;
		bool alreadyClosed;
	public:
		CloseNotifier(Flower *f) : parent(f), alreadyClosed(false) {}
		void notifyObservers(Argument *arg = 0) {
			if(!parent->isOpen && !alreadyClosed) {
				setChanged();
				Observable::notifyObservers();
				alreadyClosed = true;
			}
		}
		void open() { alreadyClosed = false; }
	} closeNotifier;
};

class Bee {
	string name;
	// An "inner class" for observing openings:
	class OpenObserver;
	friend class Bee::OpenObserver;
	class OpenObserver : public Observer {
		Bee *parent;
	public:
		OpenObserver(Bee *b) : parent(b) {}
		void update(Observable*, Argument*) {
			cout << "Bee " << parent->name << "'s breakfast time !" << endl;
		}
	} openObsrv;
	// Another "inner class" for closings:
	class CloseObserver;
	friend class Bee::CloseObserver;
	class CloseObserver : public Observer {
		Bee *parent;
	public:
		CloseObserver(Bee *b) : parent(b) {}
		void update(Observable*, Argument*) {
			cout << "Bee " << parent->name << "'s bed time!" << endl;
		}
	} closeObsrv;
public:
	Bee(string nm) : name(nm), openObsrv(this), closeObsrv(this) {}
	Observer &openObserver() { return openObsrv; }
	Observer &closeObserver() { return closeObsrv; }
};

class Hummingbird {
	string name;
	class OpenObserver;
	friend class Hummingbird::OpenObserver;
	class OpenObserver : public Observer {
		Hummingbird *parent;
	public:
		OpenObserver(Hummingbird *h) : parent(h) {}
		void update(Observable*, Argument*) {
			cout << "Hummingbird " << parent->name << "'s breakfast time !" << endl; 
		}
	} openObserv;
	class CloseObserver;
	friend class Hummingbird::CloseObserver;
	class CloseObserver : public Observer {
		Hummingbird *parent;
	public:
		CloseObserver(Hummingbird *h) : parent(h) {}
		void update(Observable*, Argument*) {
			cout << "Hummingbird" << parent->name << "'s bed time!" << endl;
		}
	} closeObserv;
	public:
		Hummingbird(string nm) : name(nm), openObserv(this), closeObserv(this) {}
		Observer &openObserver() { return openObserv; }
		Observer &closeObserver() { return closeObserv; }
};

int main() {
	Flower f;
	Bee ba("A"), bb("B");
	Hummingbird ha("A"), hb("B");
	f.openNotifier.addObserver(ha.openObserver());
	f.openNotifier.addObserver(hb.openObserver());
	f.openNotifier.addObserver(ba.openObserver());
	f.openNotifier.addObserver(bb.openObserver());
	f.closeNotifier.addObserver(ha.closeObserver());
	f.closeNotifier.addObserver(hb.closeObserver());
	f.closeNotifier.addObserver(ba.closeObserver());
	f.closeNotifier.addObserver(ba.closeObserver());
	f.openNotifier.deleteObserver(hb.openObserver());
	f.open();
	f.open();
	// Bee A does not want to go to bed
	f.closeNotifier.deleteObserver(ba.closeObserver());
	f.close();
	f.close();
	f.openNotifier.deleteObservers();
	f.open();
	f.close();
}
