#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    const char *fname = "a.txt";
    ifstream in(fname);
    string line;
    getline(in, line);
    cout << line << endl;
    cout << "strlen = " << strlen(line.c_str());
    cout << "sizeof = " << sizeof(line);
}
