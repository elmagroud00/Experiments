#ifndef PRINTVALARRAY_H
#define PRINTVALARRAY_H
#include <valarray>
#include <iostream>
#include <cstddef>

template<class T>
void print(const char *lbl, const std::valarray<T> &a) {
    std::cout << lbl << ": ";
    for(std::size_t i = 0; i < a.size(); i++) 
        std::cout << a[i] << ' ';
    std::cout << std::endl;
}

#endif // PRINTVALARRAY_H
