#include "stdafx.h"

class Dice
{
private:
	int number;
	int dice;
public:
	Dice();
	Dice(int, int);
	~Dice();
	int rollDice();
	int getNumber();
	int getDice();
};

