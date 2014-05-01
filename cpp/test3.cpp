#include <iostream>
using namespace std;

class Stack{
    struct node{
        void *data;
        int i;
    }* nodep;
public:
    Stack();
    ~Stack();
    void init();
    void print();
    void free();
};

Stack::Stack(){
    cout << "constructor" << endl;
}

Stack::~Stack(){
    cout << "deconstructor" << endl;
}

void Stack::init(){
    string *s = new string("hello world");
    nodep = new node;
    nodep->i = 1;
    nodep->data = s;
}

void Stack::free(){
    delete nodep;
}

void Stack::print(){
    string *s = static_cast<string*>(nodep->data);
    delete[] nodep;
    cout << "i = " << endl
         << "data = " << *s << endl;
}

int main(){
    Stack s;
    s.init();
    s.print();
    return 0;
}
