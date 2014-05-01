#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>
#include <cmath>
using namespace std;

int d[] = { 123, 94, 10, 314, 315 };
const int DSZ = sizeof d / sizeof *d;
bool isEvent(int x) { return x % 2 == 0; } 

int main() {
    vector<bool> vb;
    transform(d, d + DSZ, back_inserter(vb), not1(ptr_fun(isEvent)));
    copy(vb.begin(), vb.end(), ostream_iterator<bool>(cout, " "));
    cout << endl;
} /// :~
