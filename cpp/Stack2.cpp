#include <iostream>
#include <fstream>
#include <stack>
#include <list>
#include <string>
#include <cstddef>
using namespace std;

template<class Stk>
void stackOut(Stk &s, ostream &os = cout) {
    while(!s.empty()) {
        os << s.top() << "\n";
        s.pop();
    }
}

class Line {
    string line;
    size_t lspaces;
public:
    Line(string s) : line(s) {
        lspaces = line.find_first_not_of(' ');
        if(lspaces == string::npos)
            lspaces = 0;
        line = line.substr(lspaces);
    }
    friend ostream &operator<<(ostream &os, const Line &l) {
        for(size_t i = 0; i < l.lspaces; i++)
            os << ' ';
        return os << l.line;
    }
};

int main() {
    ifstream in("Stack2.cpp");
    list<Line> lines;
    string s;
    while(getline(in, s))
        lines.push_front(s);
    stack<Line, list<Line> > stk(lines);
    stackOut(stk);
}
