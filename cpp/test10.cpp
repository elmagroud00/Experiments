#include <iostream>
using namespace std;

class A {
public:
    enum { IDA = 1 };
};

class B : public A {
public:
    enum { IDA = 10, IDB = IDA + 1 };
};


int main() {
    A a;
    B b;
    cout << a.IDA << endl;
    cout << b.IDB << endl;
}
