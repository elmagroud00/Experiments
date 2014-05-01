#include <iterator>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vi(10, 0);
    ostream_iterator<int> out(cout, " ");
    vector<int>::iterator i = vi.begin();
    *i = 47;
    copy(vi.begin(), vi.end(), out);
    cout << endl;
    vi.resize(vi.capacity() + 1);
    *i= 48;
    copy(vi.begin(), vi.end(), out);
} ///:~
