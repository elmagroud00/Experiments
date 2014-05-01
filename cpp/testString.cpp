#include <iostream>
#include <string>

using namespace std;

string& func() {
    string str = "hello world";
    return str;
}

int main() {
    cout << func() << endl;
    return 0;
}
