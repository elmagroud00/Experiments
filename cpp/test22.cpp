#include <iostream>
using namespace std;

class A {
public:
	virtual void f() = 0; 
};

class B : public A {
public:
	void f() { cout << "f()" << endl;  }
};

int main() {
	B b;
	b.f();
}
