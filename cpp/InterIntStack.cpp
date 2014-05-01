#include "fibonacci.h"
#include <iostream>
using namespace std;

class IntStack {
    enum { ssize = 100 };
    int stack[ssize];
    int top;
public:
    IntStack() : top(0) {}
    void push(int i) {
        if(top >= ssize){
            cout << "Too many push()es" << endl;
            return;
        }
        stack[top++] = i;
    }
    int pop() {
        if(top <= 0) {
            cout << "Too many pop()es" << endl;
        }
        return stack[--top];
    }
    friend class IntStackIter;
};

class IntStackIter {
    IntStack &s;
    int index;
public:
    IntStackIter(IntStack &is) : s(is), index(0) {}
    int operator++() { // Prefix
        if(index >= s.top) 
            cout << "iterator moved out of range" << endl;
        return s.stack[++index];
    }
    int operator++(int) { //Postfix
        if(index >= s.top)
            cout << "iterator mived out of range" << endl;
        return s.stack[index++];
    }
};

int main(int argc, char **argv) {
    IntStack is;
    for(int i = 0; i < 20; i++)
        is.push(fibonacci(i));
    IntStackIter it(is);
    for(int j = 0; j < 21; j++)
        cout << it++ << endl;
} ///:~
