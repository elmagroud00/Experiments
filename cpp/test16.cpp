#include <iostream>
using namespace std;

int main() {
	uint64_t x = 9999;
	for(int count = 0; x; count++) {
		cout << "x = " << x << endl;
		x &= x-1;
	}
	cout << "ret = " << x << endl;
	return 0;
}
