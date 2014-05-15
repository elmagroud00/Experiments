/* ************************************************************************
  > File Name: testref.cpp
  > Author: lnmcc
  > Mail: lnmcc@hotmail.com 
  > Blog: lnmcc.net 
  > Created Time: Wed May 14 23:58:55 2014
 *********************************************************************** */
#include <iostream>

using namespace std;

class A {
public:
    A() { cout << "construct" << endl; }
    ~A() { cout << "deconstruct" << endl; }
};

A& func() {
    A* a = new A();
    return *a;
}

int main() {
   A& a = func(); 
   delete  &a;
}
