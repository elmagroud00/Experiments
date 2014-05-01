#include <stdio.h>

#define func(a, b, c)  a##b##c

int main() {
    
    func(1, 2, 3);
    return 0;
}
