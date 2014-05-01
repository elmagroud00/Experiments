#include <iostream>
using namespace std;

class A {
public:
	A() { cout << "constructor" << endl; }
	~A() { cout << "desconstructor" << endl; }
    A(const A&) { cout << "copy constructor" << endl; }	
};

void func(A &a) {
	
}

int main() {
	A a;
	func(a);	
}
