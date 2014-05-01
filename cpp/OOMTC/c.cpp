#include <iostream>

using namespace std;

class A {
public:
	A(int x) { data = x; }
	~A() {}
	A(A &a) {
		cout << "copy constructor" << endl; 
		data = a.data;
	}
	void print() {
		cout << "data = " << data << endl; 
	}
private:
	int data;
};


int main(void) {
	A a(1);
	a.print();

	A a2(a);
	a2.print();

	A a3 = a;
	a3.print();
}
