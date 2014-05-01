#include "Generators.h"
#include "PrintSequence.h"
#include <algorithm>
#include <functional>
#include <iterator>
#include <set>
#include <vector>
using namespace std;

int main() {
    vector<char> v;
    generate_n(back_inserter<char>, 50, CharGen());
    print(v.begin(), v.end(), "v", "");
    set<char> cs(v.begin(), v.end());
    typedef set<char>::iterator sci;
    for(sci it = cs.begin(); it != cs.end(); it++) {
        int n = count(v.begin(), v.end(), *it);
        cout << *it << ": " << n << ", ";
    }
    int lc = count_if(v.begin(), v.end(), bind2nd(greater<char>(), 'a'));
    cout << "\nLowercase letters: " << lc << endl;
    sort(v.begin(), v.end());
    print(v.begin(), v.end(), "sorted", "");
}
