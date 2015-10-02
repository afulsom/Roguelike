#include "ActorDef.h"


ActorDef::ActorDef()
{
}

ActorDef::ActorDef(int inTile, std::string inName, int inHP, Dice inAttack, int inDef, int inDiff)
{
	tile = inTile;
	name = inName;
	maxHP = inHP;
	attackDice = inAttack;
	defence = inDef;
	difficulty = inDiff;
}


ActorDef::~ActorDef()
{
}

int ActorDef::getTile()
{
	return tile;
}

std::string ActorDef::getName()
{
	return name;
}
int ActorDef::getHP()
{
	return maxHP;
}
Dice ActorDef::getDice()
{
	return attackDice;
}
int ActorDef::getDef()
{
	return defence;
}

int ActorDef::getDifficulty()
{
	return difficulty;
}

double ActorDef::getDifficulty(int inDiff)
{
	if (inDiff + 400 <= difficulty)
		return 0.0;
	if (inDiff > difficulty)
	{
		return ((0.0 + difficulty) / inDiff) * 10;
	}
	else
	{
		return ((0.0 + inDiff) / difficulty) * 10;
	}
}