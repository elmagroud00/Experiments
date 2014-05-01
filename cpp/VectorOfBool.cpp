#include <bitset>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
using namespace std;

int main() {
    vector<bool> vb(10, true);
    cout << "sizeof(vb) = " << sizeof(vb) << endl;
    vector<bool>::iterator it;
    for(it = vb.begin(); it != vb.end(); it++)
        cout << *it;
    cout << endl;
    vb.push_back(false);
    ostream_iterator<bool> out(cout, " ");
    copy(vb.begin(), vb.end(), out);
    cout << endl;
    bool ab[] = { true, false, false, true,true, true, true, false, false, true };
    // There is a similar constructor:
    vb.assign(ab, ab + sizeof(ab) / sizeof(bool));
    copy(vb.begin(), vb.end(), out);
    cout << endl;
    vb.flip();
    copy(vb.begin(), vb.end(), out);
    cout << endl;
    cout << "Convert to a bitset:" << endl;
    ostringstream os;
    copy(vb.begin(), vb.end(), ostream_iterator<bool>(os, ""));
    cout << "++++++++++" << endl;
    bool &x = vb.front();
    cout << "----------" << vb.size() << endl;
    cout << os.str() << endl;
    string s = "0101010101";
    bitset<10> bs(os.str());
    cout << "BitSet: " << bs << endl;

    return 0;
}

