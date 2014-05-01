#include "Bicycle.h"
#include "purge.h"
#include <cstddef>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

// Constructs a bike via a concreate builder
Bicycle buildABike(BicycleTechnician &t, BicycleBuilder *builder) {
	t.setBuilder(builder);
	t.construct();
	Bicycle *b = builder->getProduct();
	cout << "Built a " << builder->getBikeName() << endl;
	return b;
}

int main() {
	// Create an order for some bicycles
	map<string, size_t> order;
	order["mountain"] = 2;

	// Build bikes
	vector<Bicycle*> bikes;
	BicycleBuilder *m = new MountainBikeBuilder;
	BicycleTechnician tech;

}



















