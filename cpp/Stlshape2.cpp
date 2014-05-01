//Stlshape.cpp with the purge() function.
#include "purge.h"
#include <iostream>
#include <vector>
using namespace std;

class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape() {};
};

class Circle : public Shape {
public:
    void draw() { cout << "Circle::draw" << endl; }
    ~Circle() { cout << "~Circle" << endl; }
