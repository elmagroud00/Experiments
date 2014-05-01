#ifndef OBSERVER_H
#define OBSERVER_H

class Observable;
class Argument {};
class Observer {
public:
	virtual void update(Observable *o, Argument *arg) = 0;
	virtual ~Observer() {}

};
#endif // OBSERVER_H
