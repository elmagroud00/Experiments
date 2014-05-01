#ifndef PRINT_CONTAINER_H
#define PRINT_CONTAINER_H

#include "PrintSequence.h"

template<class Cont> 
void print(Cont &c, const char *nm = "",
           const char *sep = "\n",
           std::ostream &os = std::cout) {
    print(c.begin(), c.end(), nm, sep, os);
}
#endif ///:~
