#include "Bicycle.cpp"
#include <cassert>
#include <cstddef>
using namespace std;

std::string BicyclePart::names[NPARTS] = {
	"Frame", "Wheel", "Seat", "Derailleur", "Handlebar", "Sprocket", "Rack", "Shock" };

void MountainBikeBuilder::buildFrame() {
	product->addPart(new BicyclePart(BicyclePart::FRAME));
}

void MountainBikeBuilder::buildWheel() {
	product->addPart(new BicyclePart(BicyclePart::WHELL));
}

void MountainBikeBuilder::buildSeat() {
	product->addPart(new BicyclePart(BicyclePart::SEAT));
}

void MountainBikeBuilder::buildDerailleur() {
	product->addPart(new BicyclePart(BicyclePart::DERAILLEUR));
}

void MountainBikeBuilder::buildHandlebar() {
	product->addPart(new BicyclePart(BicyclePart::HANDLEBAR));
}

void MountainBikeBuilder::buildSprocket() {
	product->addPart(new BicyclePart(BicyclePart::SPROCKET));
}

void MountainBikeBuilder::buildRack() {}

void MountainBikeBuilder::buildShock() {
	product->addPart(new BicyclePart(Bicycle::SHOCK));
}

void BicycleTechnician::construct() {
	assert(builder);
	builder->createProduct();
	builder->buildFrame();
	builder->buildWheel();
	builder->buildSeat();
	builder->buildDerailleur();
	builder->buildHandbar();
	builder->buildSprocket();
	builder->buildRack();
	builder->buildShock();
}




















