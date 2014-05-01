#include <exception>
#include <iostream>
#include <cstdio>
using namespace std;

class A {};
class B {};

void my_thandler() {
    cout << "terminate called" << endl;
    exit(0);
}

void my_uhandler1() { throw A(); }
void my_uhandler2() { throw; }

void t() { throw B(); }

void f() throw(A) { t(); }
void g() throw(A, bad_exception) { t(); }

int main() {
    set_terminate(my_thandler);
    set_unexpected(my_uhandler1);
    try {
        f();
    } catch(A&) {
        cout << "caught an A from f" << endl;
    }
    set_unexpected(my_uhandler2);
    try {
        g();
    } catch(bad_exception&) {
        cout << "caught a bad_expection from g" << endl;
    }
    try {
        f();   
    } catch(...) {
        cout << "This will never print" << endl;
    }
}
