#include <cstddef>
#include <iostream>
using namespace std;

class X {
    int i;
public:
    X(int ii = 0) : i(ii) {
        cout << "This = " << this << endl;
    }
    ~X() {
        cout << "X::~X(): " << this << endl;
    }
    void *operator new(size_t, void *loc) {
        return loc;
    }
};

int main() {
    int l[10];
    cout << "l = " << l << endl;
    X *xp = new(l) X(47);
    xp->X::~X();//Explicit destructor call , ONLY use with placement
    return 0;
}
