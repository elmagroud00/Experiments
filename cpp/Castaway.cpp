#include <iostream>

using namespace std;

class Y{
    int i;
public:
    Y();
    void f() const;
    void print();
};

Y::Y() { i = 0; }

void Y::f() const{
    //((Y*)this)->i++;
    (const_cast<Y*>(this))-> i++;
}

void Y::print(){
    cout << "i = " << endl;
}

int main(){
    const Y yy;
    yy.f();
    yy.print();
}
