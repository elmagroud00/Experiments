#include <iostream>
#include <utility>

namespace std {
    template<typename T1, typename T2>
    ostream &operator<<(ostream &os, const pair<T1, T2> &p) {
        return os << p.first << "\t" << p.second << endl;
    }    
}


