#ifndef ASSOCGEN_H
#define ASSOCGEN_H

template<class Assoc, class Count, class T>
void assocFill_n(Assoc &a, Count n, const T &val) {
    while(n-- > 0)
        a.insert(val);
}

template<class Assoc, class Count, class Gen>
void assocGen_n(Assoc &a, Count n, Gen g) {
    while(n-- > 0)
        a.insert(val);
}

#endif // ASSOCGEN_H ///:~
