#include "Security.h"
#include <typeinfo>
using namespace std;

int main() {
    Metal m;
    Security &s = m;
    try {
        Investment &c = dynamic_cast<Investment&>(s);
        cout << "It is an Investment" << endl;
    } catch(bad_cast&) {
        cout << "s is not an Investment type" << endl;
        throw exception();
    }
    try {
        Bond &b = dynamic_cast<Bond&>(s);
        cout << "It is an Investment" << endl;
    } catch(bad_cast&) {
        cout << "It is not a Bond type" << endl;
        throw bad_cast(); 
    }
    cout << "bbbbbbbbbb" << endl;
}

