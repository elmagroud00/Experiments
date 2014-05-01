#include <iostream>
#include "FibonacciGenerator.h"
using namespace std;

int main() {
	FibonacciGenerator f;
	for(int i = 0; i < 20; i++)
	  cout << f.count() << ": " << f() << endl;
}
