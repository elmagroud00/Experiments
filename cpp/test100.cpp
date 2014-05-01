#include <iostream>
using namespace std;

class A {
public:
	A() { 
		cout << "constructor" << endl; 
		exit(1);
	}
	~A() { cout << "deconstructor" << endl; }
};

int main() {
	A a;
}
