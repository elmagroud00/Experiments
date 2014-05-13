/* ************************************************************************
  > File Name: testDefaultConstructor.cpp
  > Author: lnmcc
  > Mail: lnmcc@hotmail.com 
  > Blog: lnmcc.net 
  > Created Time: Tue May 13 13:39:22 2014
 *********************************************************************** */
#include <iostream>

using namespace std;

class A {
friend A& func();
private:
    A() { cout << "Constructor" << endl; };
public:
    void show() { cout << "Show" << endl; }
};

A& func() {
    A* a = new A();
    return *a;
}

int main() {
    int i = 10;
    cout << "i = " << i << endl;
    A a = func();
    a.show();
}
