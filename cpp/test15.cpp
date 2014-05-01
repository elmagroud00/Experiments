#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;

void fun(int **p) {
	int *a = (int*)malloc(4 * sizeof(int));
	memset(a, 0x00, sizeof(a));
	cout << "sizeof a = " << sizeof(a) << endl;
	a[1] = 2;
	a[2] = 3;
	copy(a, a + sizeof(a), ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << "p -> " << *p << endl;
	cout << "a -> " << a << endl;
	*p = a;
	cout << "p -> " << *p << endl;
}

int  main() {
	int *p = NULL;
	fun(&p);
 	cout << "main: p -> " << p << endl;
	cout << "sizeof p = " << sizeof(p) << endl;
	//copy(p, p + 4, ostream_iterator<int>(cout, " "));
	return 0;
}
