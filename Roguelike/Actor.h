#pragma once
#include "stdafx.h"
#include "ActorDef.h"
#include "Point.h"
#include "Pickup.h"


class Actor
{
private:
	Point loc;
	Point home;
	int currHP;
	ActorDef* def;
	int type;
	std::vector<Pickup*> inventory;
	std::vector<Pickup*> equipment;
	int chaseCounter;
	int gold;
public:
	Actor();
	Actor(ActorDef*);
	~Actor();
	void setLoc(Point);
	Point getLoc();
	int getTile();
	virtual std::string attack(int);
	virtual std::string die();
	std::string getName();
	int getHP();
	int getMaxHP();
	Dice getDice();
	int getDef();
	Point move(Point);
	virtual int getType();
	void setHP(int);
	std::string addToInventory(Pickup*);
	std::vector<Pickup*>& getInventory();
	void removeFromInventory(int);
	virtual std::string equip(Pickup*);
	std::vector<Pickup*>& getEquipment();
	ActorDef* getDefinition();
	virtual int getDamage();
	void setHome(Point);
	Point getHome();
	int getGold();
	void setGold(int);
};

