#include "NumStringGen.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

int main() {
    const int SZ = 9;
    vector<string> vs(SZ);
    //Fill it with random number strings:
    srand(time(0));
    generate(vs.begin(), vs.end(), NumStringGen());
    copy(vs.begin(), vs.end(), ostream_iterator<string>(cout, "\t"));
    cout << endl;
    const char *vcp[SZ];
    transform(vs.begin(), vs.end(), vcp, mem_fun_ref(&string::c_str));
    vector<double> vd;
    transform(vcp, vcp + SZ, back_inserter(vd), std::atof);
    cout.precision(4);
    cout.setf(ios::showpoint);
    copy(vd.begin(), vd.end(), ostream_iterator<double>(cout, "\t"));
    cout << endl;
}
