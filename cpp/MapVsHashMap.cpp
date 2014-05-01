#if defined __GNUC__ || defined __APPLE__
#include <ext/hash_map>
#else
#include <hash_map>
#endif
#include <iostream>
#include <map>
#include <ctime>
using namespace std;

int main() {
    hash_map<int ,int>  hm;
    clock_t ticks = clock();
    for(int i = 0; i < 100; i++)
        for(int j = 0; j < 1000; j++)
            hm.insert(make_pair(j, j));
    cout << "hash_map insertions: " << clock() - ticks << endl;
    return 0;
}
