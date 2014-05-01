//@//
//: TEST4.h"
#include "TEST4.h"
#include <iostream>
using namespace std;

int main() {
    void *p = new void*;
    int *q = new int;
    cout << "size of void* = " << sizeof(p) << endl;
    cout << "size of int* = " << sizeof(q) << endl;
    return 0;
}
