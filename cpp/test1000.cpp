#include <iostream>
using namespace std;

class A {
	struct B {
		int i;
		int j;
	};
public:
	A() {}
	~A() {}
	B b;
};

int main() {
	A a;
}
