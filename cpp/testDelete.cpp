#include <iostream>

using namespace std;

class A {
public:
    A() { cout << "A::A()" << endl; }
    ~A() { cout << "A::~A()" << endl; }
};

int main() {
    A* a = new A();
    delete[] a;

    return 0;
}
