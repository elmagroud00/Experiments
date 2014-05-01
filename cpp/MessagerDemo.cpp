#include <iostream>
#include <string>
using namespace std;

class Point {
public:
	int x, y, z;
	Point(int xi, yi, zi) : x(xi), y(yi), z(zi) {}
	Point(const Point &p) : x(p.x), y(p.y), z(p.z) {}
	Point &operator=(const Point &rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}
	friend ostream &operator<<(ostream &os, const Point &p) {
		return os << "x = " << p.x << "y = " << p.y << "z = " << p.z << endl;
	}
};

class Vector {
public:
	int magnitude, direction;
	Vector(int m, in d) : magnitude(m), director(d) {}
};

class Space {
public:
	static Point translate(Point p, Vector v) {
		p.x += v.magnitude + v.director;
		p.y += v.magnitude + v.director;
		p.z += v.magnitude + v.director;
		return p;
	}
};

int main() {
	Point p1(1, 2, 3);
	Point p2 = Space::tranlate(p1, Vector<11, 46>);
}
