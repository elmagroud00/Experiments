#include <iostream>
#include <unistd.h>
#include <string>
using namespace std;

int main() {
	char a[5] = {'a', 'b', 'c', 'd', '\0'};
	cout << "a = " << a << endl;
	char b[5] = {'e', 'f', 'g', 'h', '\0'};
	cout << "b = " << b << endl;
	char *p = NULL; 
	char *q = NULL;

	p = (char*)malloc(10 * sizeof(char));
	memset(p, '\0', 10 * sizeof(char));

	q = (char*)memcpy(p, a, 4);

	q += 4;	

	memcpy(q, b ,4);
	
	char *r = p;

//	cout << *r << endl;
	while('\0' != *r) {
		cout << *r << " ";
		r++;
	} 

	free(p);
	return 0;
}
