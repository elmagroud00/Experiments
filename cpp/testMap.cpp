#include <iostream>
#include <map>

using namespace std;

map<int, string> strMap;

map<int, string>& func(map<int, string>& sMap) {
    map<int, string>::iterator iter;
    for(iter = sMap.begin(); iter != sMap.end(); iter++) {
        cout << iter->first << ": " << iter->second << endl;
    }
    return sMap;
}

int main() {
    strMap.insert(pair<int, string>(1, "a"));
    strMap.insert(pair<int, string>(2, "b"));
    strMap.insert(pair<int, string>(3, "c"));

    map<int, string> amap;
    amap = func(strMap);
    func(amap);
    return 0;
}
