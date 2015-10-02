#include "Monster.h"


Monster::Monster()
{
}

Monster::Monster(ActorDef* inDef) :Actor(inDef)
{
	type = 2;
}


Monster::~Monster()
{
}

std::string Monster::die()
{
	return getName() + " dies";
}

int Monster::getType()
{
	return type;
}

