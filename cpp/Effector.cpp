#include <cassert>
#include <limits>
#include <sstream>
#include <string>
using namespace std;
typedef unsigned long ulong;

class Fixw {
    string str;
public:
    Fixw(const string &s, int width) : str(s, 0, width) {}
    friend ostream &operator<<(ostream &os, const Fixw &fw) {
        return os << fw.str;
    }
};
class Bin {
    ulong n;
public:
    Bin(ulong nn) { n = nn; }
    friend ostream &operator<<(ostream &os, const Bin &b) {
        const ulong ULMAX = numeric_limits<ulong>::max();
        ulong bit = ~(ULMAX >> 1);
        while(bit) {
            os << (b.n & bit ? '1' : '0');
            bit >>= 1;
        }
        return os;
    }
};
int main() {
    string words = "Things that make us happy, make us wise";
    for(int i = words.size(); --i >= 0;) {
        ostringstream s;
        s << Fixw(words, i);
        assert(s.str() == words.substr(0, i));
    }
    ostringstream xs, ys;
    xs << Bin(0xC);
    assert(xs.str() == "1100");
    ys << Bin(0x76543210UL);
    assert(ys.str() == "0111""0110""0100""0011""0010""0001""0000");
}
