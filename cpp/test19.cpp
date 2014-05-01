#include <iostream>
using namespace std;

class A {
public:
	A() {}
	~A() {}
	void print() { cout << "A.cout()" << endl; }
};

class B {
public:
	B() {}
	~B() {}
	void print() { cout << "B.cout()" << endl; }
	void print2() { cout << "B.cout2()" << endl; }
};

class C : public A, public B {
public:
	C() {} 
	~C() {}
	void run() { A::print(); print2(); }
};

int main() {
	C c;
	c.run();
	return 0;
}
