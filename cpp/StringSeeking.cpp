#include <cassert>
#include <sstream>
#include <string>
using namespace std;

int main(int argc, char **argv) {
    string text = "We will hook no fish";
    stringstream ss(text);
    ss.seekp(0, ios::end);
    ss << " before its time.";
    assert(ss.str() == "We will hook no fish before its time.");
    ss.seekg(8, ios::beg);
    string word;
    ss >> word;
    assert(word == "hook");
    ss.seekp(8, ios::beg);
    ss << "ship";
    ss.seekg(16, ios::beg);
    ss >> word;
    assert(word == "fish");
    ss.seekp(16, ios::beg);
    ss << "code";
    assert(ss.str() == "We will ship no code before its time.");
    ss.str("A horse of a different color.");
    assert(ss.str() == "A horse of a different color.");
} ///:~
