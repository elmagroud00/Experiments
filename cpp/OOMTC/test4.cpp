#include <iostream>
using namespace std;

class EXP {
	char *msg;
public:
	EXP(char *m) {
		cout << "Constructor" << endl;
		msg = m;	
	}
	~EXP() {
		cout << "Deconstructor" << endl;
	}
	void show() {
		cout << msg;
	}
};

int main() {
	try {
		cout << "Try block" << endl;
		EXP exp("this is a test");
		throw exp;
	} catch (EXP &x) {
		x.show();
	}
	cout << "End" << endl;
}
