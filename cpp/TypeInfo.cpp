#include <iostream>
#include <typeinfo>
using namespace std;

struct NonPolyBase {};
struct NonPolyDer : NonPolyBase { NonPolyDer(int) {} };
struct PolyBase { virtual ~PolyBase() {} };
struct PolyDer : PolyBase { PolyDer() {} };

int main() {
    const PolyDer pd;
    const PolyBase *ppb = &pd;
    cout << typeid(ppb).name() << endl;
    cout << typeid(*ppb).name() << endl;
    cout << boolalpha;
    cout << (typeid(*ppb) == typeid(pd)) << endl;
    cout << (typeid(PolyDer) == typeid(const PolyDer)) << endl;
    // Test non-polymorphic Types
    const NonPolyDer npd(1);
    const NonPolyBase *nppd = &npd;
    cout << typeid(nppd).name() << endl;
    cout << typeid(*nppd).name() << endl;
    cout << (typeid(*nppd) == typeid(npd)) << endl;
    cout << "--------------------" << endl;
    cout << typeid(PolyBase).before(typeid(NonPolyBase)) << endl;
}
