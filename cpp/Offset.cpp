#include <iostream>
using namespace std;

class A { int x; };
class B {
//	int y;
public:
	B() {}
	virtual ~B() {} 
};
class C :  public A, public B { int z; };

int main() {
	cout << "sizeof(A) == " << sizeof(A) << endl;
	cout << "sizeof(B) == " << sizeof(B) << endl;
	cout << "sizeof(C) == " << sizeof(C) << endl;
	C c;
	cout << "&c == " << &c << endl; 
	A *ap = &c;
	B *bp = &c;
	cout << "ap == " << static_cast<void*>(ap) << endl;
	cout << "bp == " << static_cast<void*>(bp) << endl;
	C *cp = static_cast<C*>(bp);
	cout << "cp == " << static_cast<void*>(cp) << endl;  
	cout << "bp == cp? " << boolalpha << (bp == cp) << endl;
	cp = 0;
	bp = 0;
	cout << bp << endl;
	B b;
	B *bpp = &b;
	C *cpp;
	cout << "bpp == " << bpp << endl;
	cout << "cpp == " << dynamic_cast<C*>(bpp) << endl;
	return 0;	
}
