#include "Dice.h"


Dice::Dice()
{
}

Dice::Dice(int inNumber, int inDice)
{
	number = inNumber;
	dice = inDice;
}


Dice::~Dice()
{
}

int Dice::rollDice()
{
	int sum = 0;
	for (int i = 0; i < number; i++)
	{
		int val = (rand() % dice) + 1;
		sum += val;
	}
	return sum;
}

int Dice::getDice()
{
	return dice;
}

int Dice::getNumber()
{
	return number;
}