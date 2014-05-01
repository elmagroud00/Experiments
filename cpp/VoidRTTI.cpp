#include <typeinfo>
#include <iostream>
using namespace std;

class Stimpy {
public:
    virtual void happy() {}
    virtual void jpy() {}
    virtual ~Stimpy() {}
};

int main() {
	Stimpy *v = new Stimpy;
	Stimpy *s = dynamic_cast<Stimpy*>(v);
	cout << typeid(*v).name() << endl;
}
