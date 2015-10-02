#pragma once
#include "Actor.h"
class Player :
	public Actor
{
private:
	int type;
	int maxHP;
	Dice attDice;
	int attackBonus;
	int defence;
	int exp;
	int level;
	int mana;
	int manaRegen;
	int HPRegen;
public:
	Player();
	Player(ActorDef*, int, int, int);
	~Player();
	std::string die();
	int getType();
	int getMaxHP();
	Dice getAttack();
	int getAttackBonus();
	int getDefence();
	int getAttackedDefence();
	void setMaxHP(int);
	void increaseMaxHP(int);
	void setAttack(Dice);
	void setAttackBonus(int);
	void setDefence(int);
	std::string attack(int);
	int getDamage();
	std::string equip(Pickup*);
	void cleanUp();
	int getExp();
	void setExp(int);
	void incExp(int);
	void levelUp();
	int getMana();
	void setMana(int);
	int getLevel();
	int getManaRegen();
	int getHPRegen();
	void regen();
};

