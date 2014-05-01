#include <cassert>
#include <cstddef>
#include <cstring>
#include <fstream>
using namespace std;

int main(int argc, char **argv) {
    const int STR_NUM = 5, STR_LEN = 30;
    char origData[STR_NUM][STR_LEN] = {
        "Hickory dickory dus ...", 
        "Are you tried of C++?",
        "Well, if you have",
        "That's just too bad,",
        "There's plenty more for us!"
    };
    char readData[STR_NUM][STR_LEN] = {{ 0 }};
    ofstream out("Poem.bin", ios::out | ios::binary);
    for(int i = 0; i < STR_NUM; i++)
        out.write(origData[i], STR_LEN);
    out.close();
    ifstream in("Poem.bin", ios::in | ios::binary);
    in.read(readData[0], STR_LEN);
    assert(strcmp(readData[0], "Hickory dickory dus ...") == 0);
    // Seek -STR_LEN byte from the end of file
    in.seekg(-STR_LEN, ios::end);
    in.read(readData[1], STR_LEN);
    assert(strcmp(readData[1], "There's plenty more for us!") == 0);
    // Absolute seek (like usine opertor[] with a file)
    in.seekg(3 * STR_LEN);
    in.read(readData[2], STR_LEN);
    assert(strcmp(readData[2], "That's just too bad,") == 0);
    // Seek backwords from current position
    in.seekg(-STR_LEN * 2, ios::cur);
    in.read(readData[3], STR_LEN);
    assert(strcmp(readData[3], "Well, if you have") == 0);
    // Seek from the beginning of the file
    in.seekg(1 * STR_LEN, ios::beg);
    in.read(readData[4], STR_LEN);
    assert(strcmp(readData[4], "Are you tried of C++?") == 0);
} ///:~
