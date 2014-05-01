#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class A {
	string s;
public:
	A() : s("hello") {}
	virtual ~A() {}
	operator const string&() { return s; }
};

int main() {
	A a;
	cout << string(a) << endl;
}
