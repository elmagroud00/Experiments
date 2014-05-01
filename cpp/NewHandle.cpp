#include <iostream>
#include <cstdlib>
#include <new>
using namespace std;

int xcount = 0;

void out_of_memory() {
    cerr << "Memory exhausted after " << xcount << " allocations!" << endl;
    exit(1);
}

int main() {
    set_new_handler(out_of_memory);
    while(1) {
        xcount++;
        new int[10000000];
        new int[10000000];
        new int[10000000];
        new int[10000000];
        new int[10000000];
    }
} ///:~
