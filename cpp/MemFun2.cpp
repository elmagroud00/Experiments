#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

class Angle {
    int degrees;
public:
    Angle(int deg) : degrees(deg) {}
    int mul(int times) { return degrees *= times; }
};

int main() {
    vector<Angle> va;
    for(int i = 0; i < 50; i += 10)
        va.push_back(Angle(i));
    int x[] = { 1, 2, 3, 4, 5 };
    transform(va.begin(), va.end(), x, ostream_iterator<int>(cout, " "), mem_fun(&Angle::mul));
}













