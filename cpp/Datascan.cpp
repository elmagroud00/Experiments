#include <fstream>
#include <iostream>
#include "DataLogger.h"
using namespace std;

int main() {
    ifstream bindata("data.bin", ios::binary);
    DataPoint d;
    while(bindata.read(reinterpret_cast<char*>(&d), sizeof d))
        cout << d << endl;
} ///:~
