#include "purge.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

class Gladiolus;
class Renuculus;
class Chrysanthemum;

class Visitor {
public:
	virtual void visit(Gladiolus *f) = 0;
	virtual void visit(Renuculus *f) = 0;
	virtual void visit(Chrysanthemum *f) = 0;
	virtual ~Visitor() {}
};

class Flower {
public:
	virtual void accept(Visitor&) = 0;
	virtual ~Flower() {}
};

class Gladiolus : public Flower {
public:
	virtual void accept(Visitor &v) {
		v.visit(this);
	}
};

class Renuculus : public Flower {
public:
	virtual void accept(Visitor &v) {
		v.visit(this);
	}
};

class Chrysanthemum : public Flower {
public:
	virtual void accept(Visitor &v) {
		v.visit(this);
	}
};

// Add the abillity to produce a string:
class StringVal : public Visitor {
	string s;
public:
	operator const string&() const { return s;}
	//const string operator string() const {return s; }
	virtual void visit(Gladiolus*) {
		s = "Gladiolus";
	}
	virtual void visit(Renuculus*) {
		s = "Renuculus";
	}
	virtual void visit(Chrysanthemum*) {
		s = "Chrydanthemum";
	}
};

// Add the ability to do "Bee" avtivities:
class Bee : public Visitor {
public:
	virtual void visit(Gladiolus*) {
		cout << "Bee and Gladiolus" << endl;
	}
	virtual void visit(Renuculus*) {
		cout << "Bee and Renculus" << endl;	
	}
	virtual void visit(Chrysanthemum*) {
		cout << "Bee and Chrysanthemum" << endl;
	}
};

struct FlowerGen {
	Flower *operator()() {
		switch(rand() % 3) {
		default:
		case 0: return new Gladiolus;
		case 1: return new Renuculus;
		case 2: return new Chrysanthemum;
		}
	}
};

int main() {
	srand(time(0));
	vector<Flower*> v(10);
	generate(v.begin(), v.end(), FlowerGen());
	vector<Flower*>::iterator it;
	// It is almost as if I added a virtual function
	// to produce a Flower string representation:
	StringVal sval;
	for(it = v.begin(); it != v.end(); it++) {
		(*it)->accept(sval);
		cout << string(sval) << endl;
	}
	// Perform "Bee" operation on all Flowers:
	Bee bee;
	for(it = v.begin(); it != v.end(); it++) 
		(*it)->accept(bee);
	purge(v);
}
