#include "stdafx.h"

class PickupDef
{
private:
	int tile;
	std::string name;
	bool isEquip;
	bool spell;
	std::string description;
	int quality;
	int type;
	int value;
	int manaCost;
public:
	PickupDef();
	PickupDef(int, std::string, int, std::function <void()>, std::string, int, int, int, int);
	~PickupDef();
	std::function <void()> useEffect;
	int getTile();
	std::string getName();
	std::string getDesc();
	bool isEquipment();
	bool isSpell();
	int getQuality();
	int getType();
	int getDifficulty();
	double getDifficulty(int);
	int getValue();
	int getManaCost();
};

