#include "Actor.h"


Actor::Actor()
{
}

Actor::Actor(ActorDef* inDef)
{
	def = inDef;
	currHP = inDef->getHP();
	loc = Point(0, 0);
	home = Point(loc);
	chaseCounter = 3;
	gold = 0;
}

Actor::~Actor()
{
}

void Actor::setLoc(Point inLoc)
{
	loc = inLoc;
}

Point Actor::getLoc()
{
	return loc;
}

int Actor::getTile()
{
	return def->getTile();
}

std::string Actor::attack(int inDamage)
{
	std::string message;
	int finalDamage;
	if ((inDamage - def->getDef()) < 0)
		finalDamage = 0;
	else
		finalDamage = inDamage - def->getDef();
	
	currHP = currHP - finalDamage;
	char* outputDamage = new char;
	sprintf_s(outputDamage, 4, "%d", finalDamage);
	message = getName() + " takes " + outputDamage + " points of damage";

	return message;
}

std::string Actor::die()
{
	return getName() + " dies";
}

std::string Actor::getName()
{
	return def->getName();
}
int Actor::getHP()
{
	return currHP;
}
int Actor::getMaxHP()
{
	return def->getHP();
}
Dice Actor::getDice()
{
	return def->getDice();
}
int Actor::getDef()
{
	return def->getDef();
}

Point Actor::move(Point dest)
{
	if (chaseCounter == 0)
	{
		setHome(loc);
		chaseCounter = 3;
		return Point(loc);
	}
	Point distance((abs(dest.X) - abs(loc.X)), (abs(dest.Y) - abs(loc.Y)));
	Point difference(dest.X - loc.X, dest.Y - loc.Y);
	if ((abs(difference.X) + abs(difference.Y)) > 3)
	{
		int tryCounter = 5;
		while (tryCounter > 0)
		{
			int random = rand() % 4;
			switch (random)
			{
			case 0: {Point homeDifference(home.X - loc.X + 1, home.Y - loc.Y);
				if ((abs(homeDifference.X) + abs(homeDifference.Y)) < 3)
				{
					return Point(loc) + Point(1, 0);
				}
				break;
			}
			case 1: {Point homeDifference(home.X - loc.X - 1, home.Y - loc.Y);
				if ((abs(homeDifference.X) + abs(homeDifference.Y)) < 3)
				{
					return Point(loc) + Point(-1, 0);
				}
				break;
			}
			case 2: {Point homeDifference(home.X - loc.X, home.Y - loc.Y + 1);
				if ((abs(homeDifference.X) + abs(homeDifference.Y)) < 3)
				{
					return Point(loc) + Point(0, 1);
				}
				break;
			}
			case 3: {Point homeDifference(home.X - loc.X, home.Y - loc.Y - 1);
				if ((abs(homeDifference.X) + abs(homeDifference.Y)) < 3)
				{
					return Point(loc) + Point(0, -1);
				}
				break;
			}
			}
			tryCounter--;
		}
		distance = Point((abs(home.X) - abs(loc.X)), (abs(home.Y) - abs(loc.Y)));
		dest = home;
	}
	else
		chaseCounter--;
	if (distance.X == 0 && distance.Y == 0)
		return Point(loc);
	else if (distance.X == 0)
	{
		if (dest.Y > loc.Y)
			return Point(loc) + Point(0, 1);
		else
			return Point(loc) + Point(0, -1);
	}
	else if (distance.Y == 0)
	{
		if (dest.X > loc.X)
			return Point(loc) + Point(1, 0);
		else
			return Point(loc) + Point(-1, 0);
	}
	else
	{
		int random = rand() % 2;
		if (random == 1)
		{
			if (dest.X > loc.X)
				return Point(loc) + Point(1, 0);
			else
				return Point(loc) + Point(-1, 0);
		}
		else
		{
			if (dest.Y > loc.Y)
				return Point(loc) + Point(0, 1);
			else
				return Point(loc) + Point(0, -1);
		}

	}
}


int Actor::getType()
{
	return 0;
}

void Actor::setHP(int inHP)
{
	currHP = inHP;
}
std::string Actor::addToInventory(Pickup* inPickup)
{
	inventory.push_back(inPickup);
	return "picked up " + inPickup->getName();
}

std::vector<Pickup*>& Actor::getInventory()
{
	return inventory;
}

void Actor::removeFromInventory(int index)
{
	inventory.erase(inventory.begin() + index);
}

std::string Actor::equip(Pickup* inEquip)
{
	if (inEquip->getEquipped())
	{
		int equipCounter = 0;
		for each(Pickup* pickup in equipment)
		{
			if (inEquip == pickup)
			{
				break;
			}
			equipCounter++;
		}
		equipment.erase(equipment.begin() + equipCounter);
		inEquip->setEquipped(false);
		return "unequipped " + inEquip->getName();
	}
	else
	{
		equipment.push_back(inEquip);
		inEquip->setEquipped(true);
		return "equipped " + inEquip->getName();
	}


}

std::vector<Pickup*>& Actor::getEquipment()
{
	return equipment;
}

ActorDef* Actor::getDefinition()
{
	return def;
}

int Actor::getDamage()
{
	return def->getDice().rollDice();
}

void Actor::setHome(Point inHome)
{
	home = inHome;
}

Point Actor::getHome()
{
	return home;
}

int Actor::getGold()
{
	return gold;
}

void Actor::setGold(int inGold)
{
	gold = inGold;
}