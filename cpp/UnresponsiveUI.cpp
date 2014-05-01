#include <iostream>
#include <fstream>
#include <string>
#include <zthread/Thread.h>

using namespace std;
using namespace ZThread;

int main() {
	cout << "Press <Enter> to quit:" << endl;
	ifstream file("UnresponsiveUI.cpp");
	string line;
	while(getline(file, line)) {
		cout << line << endl;
		Thread::sleep(1000);
	}
	cin.get();
	cout << "Shutting down..." << endl;
}
