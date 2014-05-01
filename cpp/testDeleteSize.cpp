#include <iostream>

using namespace std;

class A {
public:
    A() {}
    ~A() {}

public:
    char b[1024];
};

int main() {
    A* a = new A[10];
    cout << *((int)a - 4) << endl;
    
    return 0;
}
