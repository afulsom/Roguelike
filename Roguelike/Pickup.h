#include "stdafx.h"
#include "PickupDef.h"
#include "Point.h"

class Pickup
{
private:
	Point loc;
	PickupDef* def;
	bool isEquipped;
	int quality;
public:
	Pickup();
	Pickup(PickupDef*);
	~Pickup();
	void setLoc(Point);
	Point getLoc();
	int getTile();
	std::string getName();
	PickupDef* getDef();
	std::string use();
	void setEquipped(bool);
	bool getEquipped();
	int getQuality();
	void setQuality(int);
	int getValue();
};

