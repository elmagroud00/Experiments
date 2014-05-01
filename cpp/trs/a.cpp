#include <iostream>

using namespace std;

void go() {
    cout << "BBBB" << endl;
}


class A {
public:
        A() {}
        ~A() {}

        void show() {
           go(); 
        };
        
        void go() {
            cout << "AAA" << endl;
        }
};

int main() {
    A a;
    a.go();
    
    return 0;
}
