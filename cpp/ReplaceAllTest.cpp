#include <cassert>
#include <iostream>
#include <string>
#include "ReplaceAll.h"
using namespace std;

int main() {
    string text = "a man, a plan, a canal, Panama";
    cout << "s1 = " << text << endl;
    string s2 = replaceAll(text, "an", "XXX");
    assert(text == "a mXXX, a plXXX, a cXXXal, PXXXama");
    cout << "s2 = " << s2 << endl;
    return 0;
}
