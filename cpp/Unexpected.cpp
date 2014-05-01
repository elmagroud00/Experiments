#include <exception>
#include <iostream>
using namespace std;

class Up {};
class Fit {};
void g();

void f(int i) throw(Up, Fit) {
    switch(i) {
    case 1: throw Up();
    case 2: throw Fit();
    }
    g();
}

void g() { throw 47; }

void my_unexpected() {
    cout << "unexpected exception thrown" << endl;
    throw Up();
    //exit(0);
}

int main() {
    set_unexpected(my_unexpected);
    for(int i = 1; i <= 3; i++)
        try {
            f(i);
        } catch(Up) {
            cout << "Up caught" << endl;
        } catch(Fit) {
            cout << "Fit caught" << endl;
        }
} ///:~
