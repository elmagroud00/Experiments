#include "FileClass.h"
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
    try {
        FileClass f("FileClassTest.cppa");
        const int BSIZE = 100;
        char buf[BSIZE];
        while(fgets(buf, BSIZE, f.fp()))
            fputs(buf, stdout);
    } catch(FileClass::FileClassError &e) {
        cout << e.what() << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
} // File automaticlly closed by destructor ///:~
