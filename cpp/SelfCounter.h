#include "ValueStack.h"
#include <iostream>

class SelfCounter {
    static int counter;
    int id;
public:
    SelfCounter() : id(counter++) { std::cout << "Created: " << id << std:endl; }
    SelfCounter(const SelfCounter &rv) : id(rv.id) {
        std::cout << "Copyed: " << id << std::endl;
    }
    SelfCounter operator=(const SelfCounter &rv) {
        std::cout << "Assigned " << rv.id << "to" << id << std::endl;
        return *this;
    }
    ~SelfCounter() {
        std::cout << "Destroyed: " << id << std::endl;
    }
    friend std::ostream &operator<<(std::ostream &os, const SelfCounter &sc) {
        return os << "SelfCounter: " << sc.id;
    }
};
#endif // SELECOUNTER_H ///:~
