/* ************************************************************************
  > File Name: testRTTI.cpp
  > Author: lnmcc
  > Mail: lnmcc@hotmail.com 
  > Blog: lnmcc.net 
  > Created Time: Tue May 13 13:56:59 2014
 *********************************************************************** */
#include <iostream>
#include <typeinfo>

using namespace std;

class A {
public:
    A() { cout << "A()" << endl; }
    virtual ~A() { cout << "~A()" << endl; }
};

class B : public A {
public:
    B() { cout << "B()" << endl; }
    ~B() { cout << "~B()" << endl; }
};

int main() {
    
    A* a = new B();
    const type_info& ty = typeid(*a);
    cout << ty.name() << endl;
}
