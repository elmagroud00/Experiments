#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
    ifstream in("Stype.cpp");
    cout << in.rdbuf();
} ///:~
