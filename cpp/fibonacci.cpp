#include "fibonacci.h"
#include <cstdlib>
#include <iostream>

int fibonacci(int n) {
    const int sz = 100;
    static int f[sz];
    f[0] = f[1] = 1;
    if(n > sz)  {
        std::cout << "error, fibonacci: n is to larger" << std::endl;
        exit(1);
    }
    int i = 0;
    for(i = 0; i < sz; i++)
        if(f[i] == 0) break;
    while(i <= n) {
       f[i] = f[i - 1] + f[i - 2]; 
       i++;
    }
    return f[n]; 
} ///:~
