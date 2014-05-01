#include <iostream>
using namespace std;

class Z{
    int i;
    mutable int j;
public:
    Z();
    void f() const;
    void print();
};

Z::Z() : i(0), j(0) {}

void Z::f() const{
    j++;
}

void Z::print()
{
    cout << "hello " << endl;
}

int main(){
    Z zz;
    zz.f();
    zz.print();
}
