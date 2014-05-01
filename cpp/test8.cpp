#include <iostream>
#include <vector>

using namespace std;

class A {
public:
    A(int &aa) { a = aa; }
private:
    int &a;
};

int main() {
    int b = 1;
    cout << " b = " << b << endl;
    return 0;
}
