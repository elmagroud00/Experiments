#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
using namespace std;

int main(int argc, char **argv) {
    istringstream s("47 1.414 This is a test");
    int i;
    double f;
    s >> i >> f;
    assert(i == 47);
    double relerr = (fabs(f) - 1.414) / 1.414;
    cout << numeric_limits<double>::epsilon();
    assert(relerr <= numeric_limits<double>::epsilon());
    string buf2;
    s >> buf2;
    assert(buf2 == "This");
    cout << s.rdbuf() << endl;
}
