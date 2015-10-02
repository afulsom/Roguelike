#include "PickupDef.h"


PickupDef::PickupDef()
{
}

PickupDef::PickupDef(int inTile, std::string inName, int inCategory, std::function <void()> inUseEffect, std::string inDesc, int inQual, int inType, int inValue, int inManaCost)
{
	tile = inTile;
	name = inName;
	useEffect = inUseEffect;
	switch (inCategory)
	{
	case 0: isEquip = false; spell = false; break;
	case 1: isEquip = true; spell = false; break;
	case 2: isEquip = false; spell = true; break;
	}
	description = inDesc;
	quality = inQual;
	type = inType;
	value = inValue;
	manaCost = inManaCost;
}

PickupDef::~PickupDef()
{
}


int PickupDef::getTile()
{
	return tile;
}

std::string PickupDef::getName()
{
	return name;
}

bool PickupDef::isEquipment()
{
	return isEquip;
}

std::string PickupDef::getDesc()
{
	return description;
}

int PickupDef::getQuality()
{
	return quality;
}

int PickupDef::getType()
{
	return type;
}

int PickupDef::getDifficulty()
{
	return value;
}

double PickupDef::getDifficulty(int inDiff)
{
	if (inDiff + 400 <= value)
		return 0.0;
	if (inDiff > value)
	{
		return ((0.0 + value) / inDiff) * 10;
	}
	else
	{
		return ((0.0 + inDiff) / value) * 10;
	}
}

int PickupDef::getValue()
{
	return value;
}

bool PickupDef::isSpell()
{
	return spell;
}
int PickupDef::getManaCost()
{
	return manaCost;
}