#include <bitset>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <cstddef>
#include <iostream>
#include <string>
using namespace std;

const int SZ = 32;
typedef bitset<SZ> BS;

template<int bits> 
bitset<bits> randBitset() {
    bitset<bits> r(rand());
    for(int i = 0; i < bits / 16 - 1; i++) {
        r << 16;
        r |= bitset<bits>(rand());
    }
    return r;
}

int main() {
    srand(time(0));
    cout << "sizeof(unsigned long) = " << sizeof(unsigned long) << endl;
    cout << "sizeof(bitset<16>) = " << sizeof(bitset<16>) << endl;
    cout << "sizeof(bitset<32>) = " << sizeof(bitset<32>) << endl;
    cout << "sizeof(bitset<48>) = " << sizeof(bitset<48>) << endl;
    cout << "sizeof(bitset<64>) = " << sizeof(bitset<64>) << endl;
    cout << "sizeof(bitset<65>) = " << sizeof(bitset<65>) << endl;
    BS a(randBitset<SZ>()), b(randBitset<SZ>());
    // Converting from a bitset:
    unsigned long ul = a.to_ulong();
    cout << " a = " <<  a << endl;
    cout << " ul = " << ul << endl;
    // Converting  a string to a bitset:
    string cbits("111011010110111");
    cout << "as a string = " << cbits << endl;
    cout << BS(cbits) << " [BS(cbits)]" << endl;
    cout << BS(cbits, 2) << " [BS(cbits, 2)]" << endl;
    cout << BS(cbits, 2, 11) << " [BS(cbits, 2, 11)]" << endl;
    cout << a << " [a]" << endl;
    cout << b << " [b]" << endl;
    // Bitwise AND:
    cout << (a & b) << " [a & b]" << endl;
    cout << (a << 1) << endl;

    return 0;
}











