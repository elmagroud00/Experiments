#include <iostream>

using namespace std;

class A {
public:
	A() { cout << "constructor" << endl; }
	~A() { cout << "desconstructor" << endl; }
};

int main() {
	A** p = new A*[3] ;
	for(int i = 0; i < 3; i++)
	  p[i] = new A;
	for(int i = 0; i < 3; i++)
	  delete p[i];

	delete[] p;
}
