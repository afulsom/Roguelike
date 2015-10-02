#pragma once
#include "Actor.h"
class Monster :
	public Actor
{
private:
	int type;
public:
	Monster();
	Monster(ActorDef*);
	~Monster();
	std::string die();
	int getType();
};

