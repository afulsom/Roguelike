#include "Pickup.h"


Pickup::Pickup()
{
}

Pickup::Pickup(PickupDef* inDef)
{
	def = inDef;
	loc = Point(0, 0);
	isEquipped = false;
	quality = inDef->getQuality();
}

Pickup::~Pickup()
{
}

void Pickup::setLoc(Point inLoc)
{
	loc = inLoc;
}

Point Pickup::getLoc()
{
	return loc;
}

int Pickup::getTile()
{
	return def->getTile();
}

std::string Pickup::getName()
{
	return def->getName();
}

PickupDef* Pickup::getDef()
{
	return def;
}

std::string Pickup::use()
{
	getDef()->useEffect();
	return "used " + getDef()->getName();
}

void Pickup::setEquipped(bool inBool)
{
	isEquipped = inBool;
}

bool Pickup::getEquipped()
{
	return isEquipped;
}

int Pickup::getQuality()
{
	return quality;
}

void Pickup::setQuality(int inQual)
{
	quality = inQual;
}

int Pickup::getValue()
{
	return (int)(def->getValue() * ((0.0 + quality) / (0.0 + def->getQuality())));
}