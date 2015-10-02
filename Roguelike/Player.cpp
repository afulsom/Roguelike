#include "Player.h"


Player::Player() :Actor()
{
}

Player::Player(ActorDef* inDef, int inMana, int inManaRegen, int inHPRegen) : Actor(inDef)
{
	type = 1;
	maxHP = inDef->getHP();
	attDice = inDef->getDice();
	attackBonus = 0;
	defence = inDef->getDef();
	level = 1;
	exp = 0;
	mana = inMana;
	manaRegen = inManaRegen;
	HPRegen = inHPRegen;
}

Player::~Player()
{
}

std::string Player::die()
{
	return "You died. Press space to restart.";
}

int Player::getType()
{
	return type;
}

int Player::getMaxHP()
{
	return maxHP;
}

Dice Player::getAttack()
{
	return attDice;
}

int Player::getAttackBonus()
{
	return attackBonus;
}

int Player::getDefence()
{
	return defence;
}

int Player::getAttackedDefence()
{
	for each (Pickup* pickup in getEquipment())
	{
		if (pickup->getDef()->getType() == 2)
		{
			pickup->setQuality(pickup->getQuality() - 1);
		}
	}
	return defence;
}

void Player::setMaxHP(int inHP)
{
	maxHP = inHP;
}

void Player::increaseMaxHP(int increase)
{
	maxHP = maxHP + increase;
}

void Player::setAttack(Dice inAttack)
{
	attDice = inAttack;
}

void Player::setAttackBonus(int inBonus)
{
	attackBonus = inBonus;
}

void Player::setDefence(int inDef)
{
	defence = inDef;
}

std::string Player::attack(int inDamage)
{
	int currDefence = getAttackedDefence();
	std::string message;
	int finalDamage;
	if ((inDamage - currDefence) < 0)
		finalDamage = 0;
	else
		finalDamage = inDamage - currDefence;

	setHP(getHP() - finalDamage);
	char* outputDamage = new char;
	sprintf_s(outputDamage, 4, "%d", finalDamage);
	message = getName() + " takes " + outputDamage + " points of damage";

	return message;
}

int Player::getDamage()
{
	for each (Pickup* pickup in getEquipment())
	{
		if (pickup->getDef()->getType() == 1)
		{
			pickup->setQuality(pickup->getQuality() - 1);
		}
	}
	return getAttack().rollDice() + getAttackBonus();
}

std::string Player::equip(Pickup* inEquip)
{
	if (inEquip->getEquipped())
	{
		int equipCounter = 0;
		for each(Pickup* pickup in getEquipment())
		{
			if (inEquip == pickup)
			{
				break;
			}
			equipCounter++;
		}
		getEquipment().erase(getEquipment().begin() + equipCounter);
		inEquip->setEquipped(false);
		attDice = getDefinition()->getDice();
		attackBonus = 0;
		defence = getDefinition()->getDef();
		for each (Pickup* pickup in getEquipment())
		{
			pickup->use();
		}
		return "unequipped " + inEquip->getName();
	}
	else
	{
		inEquip->use();
		getEquipment().push_back(inEquip);
		inEquip->setEquipped(true);
		return "equipped " + inEquip->getName();
	}


}

void Player::cleanUp()
{
	for (unsigned int i = 0; i < getEquipment().size(); i++)
	{
		if (getEquipment().at(i)->getQuality() <= 0)
		{
			getEquipment().erase(getEquipment().begin() + i);
		}
	}

	for (unsigned int j = 0; j < getInventory().size(); j++)
	{
		if (getInventory().at(j)->getQuality() <= 0)
		{
			getInventory().erase(getInventory().begin() + j);
		}
	}

	attDice = getDefinition()->getDice();
	attackBonus = (level / 2);
	defence = (getDefinition()->getDef());
	for each (Pickup* pickup in getEquipment())
	{
		pickup->use();
	}
	if (exp >= pow(level, 2) * 50)
		levelUp();
}

int Player::getExp()
{
	return exp;
}

void Player::setExp(int inExp)
{
	exp = inExp;
}

void Player::incExp(int inExp)
{
	exp += inExp;
}

void Player::levelUp()
{
	maxHP += 5;
	setHP(getHP() + 5);
	level++;
}

int Player::getMana()
{
	return mana;
}

void Player::setMana(int inMana)
{
	mana = inMana;
}

int Player::getLevel()
{
	return level;
}

int Player::getManaRegen()
{
	return manaRegen;
}

int Player::getHPRegen()
{
	return HPRegen;
}

void Player::regen()
{
	if (mana < 30)
		setMana(mana + manaRegen);
	setHP(min(maxHP, getHP() + HPRegen));
}

