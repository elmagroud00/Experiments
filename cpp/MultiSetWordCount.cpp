#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
using namespace std;

int main(int argc, char **argv) {
    const char *fname = "MultiSetWordCount.cpp";
    if(argc > 1) 
        fname = argv[1];
    ifstream in(fname);
    multiset<string> wordmset;
    string word;
    while(in >> word) 
        wordmset.insert(word);
    typedef multiset<string>::iterator MSit;
    MSit it = wordmset.begin();
    while(it != wordmset.end()) {
        pair<MSit, MSit> p = wordmset.equal_range(*it);
        int count = distance(p.first, p.second);
        cout << *it << ": " << count << endl;
        it = p.second; // Move to the next word
    }
} /// :~
