#include <fstream>
#include <iostream>
using namespace std;

#define D(A) T << #A << endl; A

int main() {
    ofstream T("format.out");
    D(int i = 47);
    D(float f = 2300114.414159);
    const char *s = "Is there any more?";
    D(T.setf(ios::unitbuf);)
    D(T.setf(ios::showbase);)
    D(T.setf(ios::uppercase | ios::showpos);)
    D(T << i << endl;) //Default is dec
    D(T.setf(ios::hex, ios::basefield);)
    D(T << i << endl;)
    D(T.unsetf(ios::showbase);)
    D(T.setf(ios::dec, ios::basefield);)
    D(T.setf(ios::left, ios::adjustfield));
    D(T.fill('0');)
    D(T << "file char: " << T.fill() << endl;)
    D(T.width(10);)
    T << i << endl;
    D(T.setf(ios::internal, ios::adjustfield);)
    D(T.width(10);)
    T << i << endl;
    D(T << i << endl;)
    D(T.unsetf(ios::showpos);)
    D(T.setf(ios::showpoint);)
    D(T << "prec = " << T.precision() << endl;)
    D(T.setf(ios::scientific, ios::floatfield);)
    D(T << f << endl;)
    D(T.precision(20);)
    D(T << "prec = " << T.precision() << endl;)
    D(T << endl << f << endl;)
    D(T.setf(ios::scientific, ios::floatfield);)
    D(T.width(10);)
    T << s << endl;
    D(T.width(40);)
    T << s << endl;
    D(T.setf(ios::left, ios::adjustfield);)
    D(T.width(40);)
    T << s << endl;
} ///:~
