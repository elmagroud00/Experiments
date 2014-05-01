#include <iostream>
using namespace std;

class A {
public:
	int i;
	int j;
	A() : i(j) {};
	~A() {};
};

int main() {
	A a;
}
