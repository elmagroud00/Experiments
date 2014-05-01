#ifndef ITERSTACKTEMPLATE_H
#define ITERSTACKTEMPLATE_H
#include <iostream>

template<class T, int ssize = 100>
class StackTemplate {
    T stack[ssize];
    int top;
public:
    StackTemplate() : top(0) {}
    void push(const T &i) {
        if(top >= ssize)
            std::cout << "Too many push()es" << std::endl;
        stack[top++] = i;
    }
    T pop() {
        if(top <= 0)
            std::cout << "Too many pop()es" << std::endl;
        return stack[--top++];
    }
    class iterator;
    friend class iterator;
    class iterator {
        StackTemplate &s;
        int index;
    public:
        iterator(StackTemplate &st) : s(st), index(0) {}
        iterator(StackTemplate &st, bool) : s(st), index(s.top){} 
        T operator*()const { return s.stack[index]; }
        T operator++() {
            if(index >= s.top)
                std::cout << "iterator moved out of range" << std::endl;
            return s.stack[++index];
        }
        T operator++(int) {
            if(index >= s.top)
                std::cout << "iterator moved out of range" << std::endl;
            return s.stack[index++];
        }   
       iterator &operator+=(int amount) {
            if(index + amount >= s.top)
                std::cout << "tried to move out of bounds" << std::endl;
            index += amount;
            return *this;
       }
       bool operator==(const iterator &rv) const {
            return index == rv.index;
       }
       bool operator!=(const iterator &rv) const {
            return index != rv.index;
       }
       friend std::ostream &operator<<(std::ostream &os, const iterator &it) {
            return os << *it;
       }
    };
    iterator begin() { return iterator(*this); }
    iterator end() { return iterator(*this, true); }
};
#endif // ITERSTACKTEMPLATE_H ///:~
