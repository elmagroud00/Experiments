#include <algorithm>
#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <string>

using namespace std;

char replaceJunk(char c) {
    // Only keep alphas, space (as a delimter)
    return (isalpha(c) || c == '\'') ? c : ' ';
}

int main(int argc, char **argv) {
    char *fname = "WordList.cpp";
    if(argc > 1) fname = argv[1];
    ifstream in(fname);
    set<string> wordlist;
    string line;
    while(getline(in, line)) {
        transform(line.begin(), line.end(), line.begin(), replaceJunk);
        istringstream is(line);
        string word;
        while(is >> word)
            wordlist.insert(word);
    }
    copy(wordlist.begin(), wordlist.end(), ostream_iterator<string>(cout, "\n"));
} ///:~
