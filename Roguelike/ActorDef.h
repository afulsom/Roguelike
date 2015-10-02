#include "stdafx.h"
#include "Dice.h"

class ActorDef
{
private:
	int tile;
	std::string name;
	int maxHP;
	Dice attackDice;
	int defence;
	int difficulty;
public:
	ActorDef();
	ActorDef(int, std::string, int, Dice, int, int);
	~ActorDef();
	int getTile();
	std::string getName();
	int getHP();
	Dice getDice();
	int getDef();
	int getDifficulty();
	double getDifficulty(int);
};

