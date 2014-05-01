#include <fstream>
#include <iostream>
using namespace std;

int main(int agrc, char ** argv) {
    ifstream in("Sbufget.cpp");
    streambuf &sb = *cout.rdbuf();
    while(!in.get(sb).eof()) {
        if(in.fail())
            in.clear();
        cout << char(in.get());
    }
} ///:~
