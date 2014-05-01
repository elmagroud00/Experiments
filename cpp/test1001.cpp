#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	ifstream In;
	string temp;
	
	In.open("test1001.cpp");
	
	while(!In.eof()) {
		In >> temp;
		cout << temp << endl;
	}
	return 0;
}
