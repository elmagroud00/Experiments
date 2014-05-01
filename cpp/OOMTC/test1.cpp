#include <iostream>

using namespace std;

int main() {
	char a[] = "12345";
	
	cout << "a[4] = " << a[4] << endl;
	cout << "a[5] = " << a[5] << endl;
	cout << "strlen" << strlen(a) << endl;
	cout << "sizeof" << sizeof(a) / sizeof(char) << endl; 

	

	return 0;
}
