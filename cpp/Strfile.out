#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
    const int SZ = 100;
    char buf[SZ];
    {
        ifstream in("Strfile.cpp");
        ofstream out("Strfile.out");
        int i = 1; // Line counter
        while(in.getline(buf, SZ)) {
            out << buf << endl;
        }
      /*  while(in.get(buf, SZ)) {
            in.get(); // Throw away next character(\n)
            cout << buf << endl;
            out << i++ << ": " << buf << endl;
        } */
    } // Destructors close in & out
    ifstream in("Strfile.out");
    while(in.getline(buf, SZ)) {
        char *cp = buf;
        while(*cp != ':')
            ++cp;
        cp += 2;
        cout << cp << endl;
    }
} /// :~
