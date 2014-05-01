#ifndef VALUESTACK_H
#define VALUESTACK_H

template<class T, int ssize = 100>
class Stack {
    T stack[ssize];
    int top;
public:
    Stack() : top(0) {}
    void push(const T &x) {
        if(top >= ssize) {
            std::cout << "Too many push() es" << endl;
            return;
        }
        stack[top++] = x;
    }
    T peek() const { return stack[top]; }
    T pop() {
        if(top < 0) {
            std::cout << "Too many pop()es" << endl;
            return;
        }
        return stack[--top];
    }
}; 
#endif // VALUESTACK_H ///:~
