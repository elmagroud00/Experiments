#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream in;
	string line;
	string filename = "test40.cpp";
	in.open(filename.c_str(), ifstream::in);
	while(getline(in, line)) 
	  cout << line << endl;

	return 0;
}
