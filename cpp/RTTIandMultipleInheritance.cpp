#include <iostream>
#include <typeinfo>
using namespace std;

class BB {
public:
	virtual void f() {}
	virtual ~BB() {}
};

class B1 : virtual public BB {};
class B2 : virtual public BB {};
class MI : public B1, public B2 {};

int main() {
	BB *bbp = new MI;
	cout << typeid(*bbp).name() << endl;
	MI *mip = dynamic_cast<MI*>(bbp);
	cout << typeid(mip).name() << endl;	
}

