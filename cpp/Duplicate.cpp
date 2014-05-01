#include <iostream>
using namespace std;

class Top;

void print(Top &t);

class Top {
public:
	int x;
	Top(int n) { x= n; }
	friend void print(Top &t);
};

class Left : public Top {
	int y;
public:
	Left(int m, int n) : Top(m) { y = n; }
};

class Right : public Top {
	int z;
public:
	Right(int m, int n) : Top(m) { z = n; }
};

class Botton : public Left, public Right {
	int w;
public:
	Botton(int i, int j, int k, int m) : Left(i, k), Right(j, k) { w = m; }
};

void print(Top &t){
	cout << t.x << endl;
}

int main() {
	Botton b(1, 2, 3, 4);
	cout << sizeof(b) << endl;
	cout << "Top.x == " << b.x << endl; 
}
