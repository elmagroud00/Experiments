#include "Trash.h"
#include "purge.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <typeinfo>
#include <utility>
#include <vector>
using namespace std;

// Comparator for type_info pointers
struct TInfoLess {
	bool operator()(const type_info *t1, const type_info *t2) const {
		return t1->before(*t2);
	}
};

typedef map<const type_info*, vector<Trash*>, TInfoLess> TrashMap;

// Sums up the value of the Trash in a bin:





















