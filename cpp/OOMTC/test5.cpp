#include <cstdio>
#include <iostream>
using namespace std;

void func(const char *m) {
	const char *msg;
	msg = m;
	cout << msg << endl;
}

int main() {
	const char *x = "hello";
	func(x);
	x = "apple";
}
