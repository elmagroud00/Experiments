#include <iostream>
#include <pthread.h>
#include <set>
#include <algorithm>
using namespace std;

class  rational {
public:
	rational(const int num, const int den) { numerator = num; denominator = den; }
	rational() { numerator = 0; denominator = 1; }
	rational(const rational& a) { 
		numerator = a.numerator;
		denominator = a.denominator;
	}
	
	virtual ~rational() {};
	
	rational(rational &l, rational &r) {
		l.numerator = r.numerator;
		l.denominator = r.denominator;
	}

	friend ostream &operator<<(ostream &os, const rational &a) {
		return os << a.numerator << "/" << a.denominator << endl;
	}

	bool operator<(const rational &a) {
		return ((numerator / denominator) > (a.numerator / a.denominator));	
	}

	bool operator>(const rational &a) {
		return !((numerator / denominator) > (a.numerator / a.denominator));	
	}

	bool operator==(const rational &a) {
		return ((numerator / denominator) == (a.numerator / a.denominator));	
	}

private:
	int numerator;
	int denominator;
};

rational M(3, 4);
typedef set<rational, rational> rational_set;
typedef set<rational, rational>::iterator rational_iterator;
rational_set SetA, SetB, SetC;
rational_iterator A, B, C;

void *threadA(void *X) {
	rational Z(5, 4);
	rational W(1, 8);
	SetA.insert(W);
	SetA.insert(Z);
	set_intersection(SetA.begin(), SetA.end(), SetB.begin(), SetB.end(), inserter(SetC, SetC.begin()));
	SetB.insert(W);
	SetA.erase(SetA.begin(), SetA.end());
}

void *threadB(void *X) {
	rational Q(2, 3);
	rational R(5, 5);
	SetB.insert(Q);
	SetB.insert(R);
	SetA.insert(Q);
	SetA.insert(M);
	set_union(SetC.begin(), SetC.end(), SetB.begin(), SetB.end(), inserter(SetA, SetA.begin()));
}

int main(void) {
	pthread_t ThreadA, ThreadB;
	pthread_create(&ThreadA, NULL, threadA, NULL);
	pthread_create(&ThreadB, NULL, threadB, NULL);
	pthread_join(ThreadA, NULL);
	pthread_join(ThreadB, NULL);
	A = SetA.begin();
	B = SetB.begin();
	C = SetC.begin();
	cout << "Set A contains: ";
	while(A != SetA.end()) {
		cout << *A << " ";
		A++;
	}
	cout << endl << "Set B contails: ";
	while(B != SetB.end()) {
		cout << *B << " ";
		B++;
	}
	while(C != SetC.end()) {
		cout << *C << " ";
		C++;
	}
	cout << endl;
	return 0;
}
