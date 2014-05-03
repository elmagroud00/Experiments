/* ************************************************************************
  > File Name: a.cpp
  > Author: lnmcc
  > Mail: lnmcc@hotmail.com 
  > Blog: lnmcc.net 
  > Created Time: Sun May  4 00:07:40 2014
 *********************************************************************** */
#include <iostream>
using namespace std;

class A {
public:
    A(int i) : m_i(i) {}
    void show() {
        cout << m_i << endl;
    }

    int m_i;
};

class B : virtual public A {
public:
   B(int i) : A(i + 2) {}
};

class C : virtual public A {
public:
    C(int i) : A(i + 1) {}
};

class D : public B, public C {
public:
    D(int i) : B(i), C(i), A(i) {}
};

int main() {
    D d(1);
    
    //static_cast<B>(d).show();
    d.show();

    return 0;
}
