#include <iostream>
#include <fstream>
#include <string>
#include <cerrno>

using namespace std;

class DisplayTask {
	ifstream in;
	string line;
public:
	DisplayTask(const string &file) {
		in.open(file.c_str(), ifstream::in);
		if(in.fail()) {
			cerr << "open fiai" << endl;
		}
	}
	~DisplayTask() { in.close(); }
	void run() {
		while(getline(in, line)) {
			cout << line << endl;
		}
	}
};

int main() {
		cout << "Press <Enter> to quit:" << endl;
		DisplayTask *dt = new DisplayTask("tesiiit40.cpp");
		dt->run();
		cin.get();
			
	cout << "Shutting down..." << endl;
}
