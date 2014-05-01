#include <iostream>
using namespace std;

struct A {
	int a;
};

struct B : public A {
	int b;
};

struct C : public A {
	int c;
};

struct D {
	B ob;
	C oc;
};

void func(D *d) {
	cout << d->ob.a << endl;
	cout << d->ob.b << endl;
	cout << d->oc.a << endl;
	cout << d->oc.c << endl;
}

int main() {
	D d;
	d.ob.a = 1;
	d.ob.b = 2;
	d.oc.a = 3;
	d.oc.c = 4;
	func(&d);

	return 0;
}
