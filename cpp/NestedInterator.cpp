#include "fibonacci"
#include <iostream>
#include <string>
using namespace std;

class IntStack {
    enum { ssize = 100 };
    int stack[ssize];
    int top;
public:
    IntStack() : top(0) {}
    void push(int i) {
        if(top >= ssize) 
           cout << "Too many push()es" << endl;
        stack[top++] = i;
    }
    int pop() {
        if(top <= 0)
            cout << "Too many pop()es" << endl;
        return stack[--top];
    }
    class interator;
    friend class iterator;
    class iterator {
        IntStack &s;
        int index;
    public:
        iterator(IntStack &is) : s(is), index(0) {}
        iterator(IntStack &is, bool) : s(is), index(s.top) {}
        int current() const { return s.stack[index]; }
        int operator++() {
            if(index >= s.top)
                cout << "iterator moved out of range" << endl;
            return s.stack[++index];
        }
        int operator++(int) {
            if(index >= s.top)
                cout << "iterator moved out of range" << endl;
            return s.stack[index++];
        }
        iterator &operator+=(int amount) {
            if(index + amount >= s.top)
                cout << "tried to moved out of bounds" << endl;
            index += amount;
            return *this;
        }
        bool operator==(const iterator &rv) const {
            return index == rv.index;
        }
        bool operator!=(const iterator &rv) const {
            return index != rv.index;
        }
        friend ostream &operator<<(ostream &os, const iterator &it) {
            return os << itcurrent();
        }
    };
    iterator begin() { return iterator(*this); }
    iterator end() { return iterator(*this, true); }
};

int main() {
    IntStack is;
    for(int i = 0; i < 20; i++)
        is.push(fibonacci(i));
    cout << "Traverse the whole IntStack\n";
    IntStack::iterator it = is.begin();
    while(it != is.end())
        cout << it++ << endl;
    cout << "Traverse a portion of the IntStack" << endl;
    IntStack::iterator start = is.begin();
    IntStack::iterator end = is.begin();
}












