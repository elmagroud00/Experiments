#include <iostream>
using namespace std;

class A {
public:
	class B {
	public:
		B() { cout << "B::construction" << endl; }
	};
public:
	A() { cout << "A::construction" << endl; }
};

int main() {
	A a;
	A::B b;
}
