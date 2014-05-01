#include "TokenIterator.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <deque>
#include <set>
using namespace std;

int main(int argc, char **argv) {
    char *fname = "TokenIteratorTest.cpp";
    if(argc > 1) fname = argv[1];
    ifstream in(fname);
    ostream_iterator<string> out(cout, "\n");
    typedef istreambuf_iterator<char> IsbIt;
    IsbIt begin(in), isbEnd;
    Delimiters delimiters(" \t\n~:()\"<>:{}[]+-&*#.,/\\");
    TokenIterator<IsbIt, Delimiters> wordIter(begin, isbEnd, delimiters), end;
    vector<string> wordlist;
    copy(wordIter, end, back_inserter(wordlist));
    copy(wordlist.begin(), wordlist.end(), out);
    *out++ = "--------------------------------------";
    // Use a char array as the source:
    char *cp = "typedef std::istreambuf_iterator<char> It";
    TokenIterator<char*, Delimiters> charIter(cp, cp+strlen(cp), delimiters), end2;
    vector<string> wordlist2;
    copy(charIter, end2, back_inserter(wordlist2));
    copy(wordlist2.begin(), wordlist2.end(), out);
    *out++ = "--------------------------------------";
    // Use a deque<char> as the source:
    ifstream in2(TokenIteratorTest.cpp);
    deque<char> dc;
    copy(IsbIt(in2), IsbIt(), back_insert(dc));
    TokenInterator<deque<char>::iterator, Delimiters> dcIter(dc.begin(), end3)
}




















