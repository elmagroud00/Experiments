#include <cassert>
#include <cmath>
#include <iomanip>
#include <limits>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

int main() {
    istringstream is("one 2.34 five");
    string temp;
    is >> setw(2) >> temp;
    assert(temp == "on");
    is >> setw(3) >> skipws >> temp;
    cout << temp << endl;
    //assert(temp == "e");
   /* double x;
    is >> setw(2) >> x;
    cout << x << endl;
    double relerr = fabs(x - 2.34) / x;
    assert(relerr <= numeric_limits<double>::epsilon()); */
} /// :~
