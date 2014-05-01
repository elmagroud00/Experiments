#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <string>

using namespace std;

class A {
public:
    A() { cout << "A::A()" << endl; }
    ~A() { cout << "A::~A()" << endl; }
};

int main(int argc, char **argv) {
    char *fname = "WordList2.cpp";
    if(argc > 1) fname = argv[1];
    ifstream in(fname);
    istreambuf_iterator<char> p(in), end;
    set<string> wordlist;
    while(p != end) {
        string word;
        A a;
        insert_iterator<string> ii(word, word.begin());
        // Find the first alpha character:
        while(p != end && !isalpha(*p))
            ++p;
        // Copy until the first non-alpha character:
        while( p != end && isalpha(*p))
            *ii++ = *p++;
        if(word.size() != 0)
            wordlist.insert(word);
    }
    copy(wordlist.begin(), wordlist.end(), ostream_iterator<string>(cout, "\n"));
} ///:~










