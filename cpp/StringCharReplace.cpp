#include <algorithm>
#include <iostream>
#include <cassert>
#include <string>
using namespace std;

int main() {
    string s("aaaXaaaXXaaXXXaXXXXXaaa");
    replace(s.begin(), s.end(), 'X', 'Y');
    cout << s << endl;
}
