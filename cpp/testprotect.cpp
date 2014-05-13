/* ************************************************************************
  > File Name: testprotect.cpp
  > Author: lnmcc
  > Mail: lnmcc@hotmail.com 
  > Blog: lnmcc.net 
  > Created Time: Wed May  7 23:29:29 2014
 *********************************************************************** */
#include <iostream>

using namespace std;

class A {
public:
    A() : i(100) {}
protected:
    int i;
};

class B : public A {
public:
    void show() {
        cout << i << endl;
    }
};

class C : public B {
public:
    void show() {
        cout << i << endl;
    }
};

int main() {
    C c;
    c.show();
}

