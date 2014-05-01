#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>
#include "DataLogger.h"
using namespace std;

int main() {
    time_t timer;
    srand(time(&timer)); // Seed the random number generator
    ofstream data("data.txt");
    ofstream bindata("data.bin", ios::binary);
    for(int i = 0; i < 100; i++, timer += 55) {
        // Zero to 199 meters:
        double newdepth = rand() % 200;
        double fraction = rand() % 100 + 1;
        newdepth += 1.0 / fraction;
        double newtemp = 150 + rand() % 200;
        fraction = rand() % 100 + 1;
        newtemp += 1.0 / fraction;
        const DataPoint d(timer, Coord(45, 20, 31), Coord(22, 34, 18), newdepth, newtemp);
        data << d << endl;
        bindata.write(reinterpret_cast<const char*>(&d), sizeof(d));
    }
} /// :~
