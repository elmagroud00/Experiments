#include <iostream>
#include <string>
using namespace std;

class M {
public:
	M(const string &s) { cout << "M " << s << endl; }
};

class A {
	M m;
public:
	A(const string &s) : m(" in A") {
		cout << "A " << s << endl;
	}
	virtual ~A() {}
};

class B {
	M m;
public:
	B(const string &s) : m(" in B") {
		cout << "B " << s << endl;
	}
	virtual ~B() {}
};

class C {
	M m;
public:
	C(const string &s) : m(" in C") {
		cout << "C " << s << endl;
	}
	virtual ~C() {}
};

class D {
	M m;
public:
	D(const string &s) : m(" in D") {
		cout << "D " << s << endl;
	}
	virtual ~D() {}
};

class E : public A, virtual public B, virtual public C {
	
};









