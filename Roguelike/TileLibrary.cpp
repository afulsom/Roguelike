#include "tilelib.h"
#include "TileLibrary.h"

TileLibrary::TileLibrary()
{
	
}

TileLibrary::~TileLibrary()
{

}
void TileLibrary::drawTile(int number, Point point)
{
	tl_rendertile(number, point.X, point.Y);
}

void TileLibrary::drawTile(char character, Point point)
{
	tl_rendertile(character, point.X, point.Y);
}

bool TileLibrary::keyPressed(char* key)
{
	return tl_keywentdown(key);
}

void TileLibrary::frameStart(int col)
{
	tl_framestart(col);
}

int TileLibrary::getXRes()
{
	return tl_xres();
}

int TileLibrary::getYRes()
{
	return tl_yres();
}

void TileLibrary::initialize(char* name, int xRes, int yRes, char* file, int tileSize, int sizes)
{
	tl_init(name, xRes, yRes, file, tileSize, sizes);
}

void TileLibrary::shutDown()
{
	tl_shutdown();
}

void TileLibrary::frameRender(World& level, Player* player, int state)
{
	if (state == 2 || state == 3)
	{
		for (int x = 0; x < getXRes(); x++)
		{
			for (int y = 0; y < getYRes(); y++)
			{
				drawTile(0x100, Point(x, y));
			}
		}
		if (state == 2)
		{
			color(0x000033FF);
			renderString((std::string)"Welcome", Point(3, 3));
			setScale(2);
			color(0xFFFFFFFF);
			renderString((std::string)"1 - Arcane Archer", Point(6, 10));
			renderString((std::string)"2 - Assassin", Point(6, 12));
			renderString((std::string)"3 - Slayer", Point(6, 14));
			renderString((std::string)"Space - Pause", Point(6, 16));
			renderString((std::string)"Esc - Exit", Point(6, 18));
		}
		else if (state == 3)
		{
			color(0x000033FF);
			renderString((std::string)"Welcome", Point(3, 3));
			setScale(2);
			color(0xFFFFFFFF);
			renderString((std::string)"Enter - Restart", Point(6, 10));
			renderString((std::string)"Space - Unpause", Point(6, 12));
			renderString((std::string)"Esc - Exit", Point(6, 14));
		}	
	}
	else if (state == 1)
	{
		Point worldPoint;
		hoverMessage = "";
		worldPoint.Y = player->getLoc().Y - (this->getYRes() / 2);
		worldPoint.X = player->getLoc().X - (this->getXRes() / 2);
		level.deFoW(player->getLoc(), 4);
		level.loop_xy(worldPoint, Point(getXRes() - 6, (getYRes() - 2)), [&](Cell& inCell){
			if (!inCell.getFog())
			{
				this->drawTile(inCell.getNumber(), (inCell.getPoint() - worldPoint));
				if (inCell.getAccent() != 0)
				{
					drawTile(inCell.getAccent(), inCell.getPoint() - worldPoint);
				}
				if (inCell.getPickup() != nullptr)
				{
					if (inCell.getPickup()->getDef()->isSpell())
						drawTile(0x31D, (inCell.getPoint() - worldPoint));
					drawTile(inCell.getPickup()->getTile(), (inCell.getPoint() - worldPoint));
					if ((inCell.getPoint() - worldPoint) == Point(getMouseX(), getMouseY()))
					{
						hoverMessage = inCell.getPickup()->getName();
						hoverMessage.append(":" + inCell.getPickup()->getDef()->getDesc());
					}
				}
				if (inCell.getActor() != nullptr)
				{
					drawTile(inCell.getActor()->getTile(), (inCell.getPoint() - worldPoint));
					if ((inCell.getPoint() - worldPoint) == Point(getMouseX(), getMouseY()))
					{
						hoverMessage = inCell.getActor()->getName();
						char* hpOutput = new char;
						sprintf_s(hpOutput, 10, "%d", inCell.getActor()->getHP());
						hoverMessage.append(":  HP:");
						hoverMessage.append(hpOutput);
						std::string att = "";
						int attThreat = inCell.getActor()->getDice().getDice() * inCell.getActor()->getDice().getNumber();
						if (attThreat > 15)
							att = "Deadly";
						else if (attThreat > 10)
							att = "Strong";
						else if (attThreat > 5)
							att = "Moderate";
						else
							att = "Weak";
						hoverMessage.append(" ATT:" + att);
					}
				}
			}
			else
			{
				color(0x808080FF);
				this->drawTile(inCell.getNumber(), (inCell.getPoint() - worldPoint));
				color(0xFFFFFFFF);
			}

		});
		color(0xFFFFFFFF);
		renderStats(player);
		renderInventory(player);
		if (level.getCell(player->getLoc()).getType() == 3)
			renderShop(level.getShopInv());
	}
}

void TileLibrary::movement(World& level, Actor* mover, Point nextPoint)
{
	Point currPoint = mover->getLoc();

	if (nextPoint == currPoint)
		return;
	if (level.getType(nextPoint) == 1)
	{
		nextPoint = currPoint;
	}
	else if (level.getCell(nextPoint).getActor() != nullptr)
	{
		if (mover->getType() != level.getCell(nextPoint).getActor()->getType())
		{
			level.getLog().addToLog(level.getCell(nextPoint).getActor()->attack(mover->getDamage()), level.getLog().getTurnCounter(), 0xFFFFFFFF);
			playSound("hit.sfs");
		}
		nextPoint = currPoint;
	}
	else if (level.getCell(nextPoint).getPickup() != nullptr)
	{
		if (mover->getType() == 1)
		{
			if (mover->getInventory().size() < 12)
			{
				playSound("coin.sfs");
				level.getLog().addToLog(mover->addToInventory(level.getCell(nextPoint).getPickup()), level.getLog().getTurnCounter(), 0xFFFFFFFF);
				level.getCell(nextPoint).getPickup()->setLoc(Point(0, 0));
				level.getCell(nextPoint).setPickup(nullptr);
			}
			else
			{
				level.getLog().addToLog("Inventory is full.", level.getLog().getTurnCounter(), 0xFFFFFFFF);
			}
			
		}
	}
	level.getCell(currPoint).setActor(nullptr);
	level.getCell(nextPoint).setActor(mover);
	mover->setLoc(nextPoint);

	

}

int TileLibrary::playerInput(World& level, Player* mover, int state)
{
	switch (state)
	{
	case 1:
		if (mover->getHP() <= 0)
		{
			if (keyPressed("space"))
				return 4;
			return 0;
		}
		else
		{
			if (keyPressed("space"))
				return 3;
			Point currPoint = mover->getLoc();
			Point nextPoint = currPoint;
			if (level.areStairsFound())
			{
				if (keyPressed("return"))
				{
					playSound("stairs.sfs");
					return 1;
				}
			}
			if (buttonWentDown(1))
			{
				if (currHighlight >= 0)
				{
					if (level.getCell(currPoint).getType() == 3)
					{
						level.getLog().incTurnCounter(1);
						if (currHighlight >= 24)
						{
							int shopIndex = currHighlight - 24;
							//buy
							if (mover->getGold() >= (level.getShopInv()[shopIndex]->getValue() * 1.5))
							{
								mover->setGold(mover->getGold() - (int)((double)level.getShopInv()[shopIndex]->getValue() * 1.5));
								mover->addToInventory(level.getShopInv()[shopIndex]);
								level.removeFromShop(shopIndex);
								playSound("coin.sfs");
							}
							else
								level.getLog().addToLog("Not enough gold.", level.getLog().getTurnCounter(), 0xFFFFFFFF);
						}
						else
						{
							//sell
							mover->setGold(mover->getGold() + mover->getInventory()[currHighlight]->getValue());
							level.addToShop(mover->getInventory()[currHighlight]);
							mover->removeFromInventory(currHighlight);
							playSound("coin.sfs");
						}
					}
					else
					{
						level.getLog().incTurnCounter(1);
						if (mover->getInventory()[currHighlight]->getDef()->isEquipment())
						{
							level.getLog().addToLog(mover->equip(mover->getInventory()[currHighlight]), level.getLog().getTurnCounter(), 0xFFFFFFFF);
							playSound("equip.sfs");
						}
						else if (mover->getInventory()[currHighlight]->getDef()->isSpell())
						{
							if (mover->getMana() >= mover->getInventory()[currHighlight]->getDef()->getManaCost())
							{
								mover->setMana(mover->getMana() - mover->getInventory()[currHighlight]->getDef()->getManaCost());
								level.getLog().addToLog(mover->getInventory()[currHighlight]->use(), level.getLog().getTurnCounter(), 0xFFFFFFFF);
								//level.getLog().addToLog(mover->getInventory()[currHighlight]->getDef()->getName() + ": " + mover->getInventory()[currHighlight]->getDef()->getDesc(), level.getLog().getTurnCounter(), 0xFFFFFFFF);
								playSound("item.sfs");
							}
							else
								level.getLog().addToLog("Insufficient Mana.", level.getLog().getTurnCounter(), 0xFFFFFFFF);
						}
						else
						{
							level.getLog().addToLog(mover->getInventory()[currHighlight]->use(), level.getLog().getTurnCounter(), 0xFFFFFFFF);
							level.getLog().addToLog(mover->getInventory()[currHighlight]->getDef()->getName() + ": " + mover->getInventory()[currHighlight]->getDef()->getDesc(), level.getLog().getTurnCounter(), 0xFFFFFFFF);
							mover->removeFromInventory(currHighlight);
							playSound("item.sfs");
						}
					}

				}

			}
			else if (keyPressed("left"))
			{
				level.getLog().incTurnCounter(1);
				nextPoint.X -= 1;
			}
			else if (keyPressed("right"))
			{
				level.getLog().incTurnCounter(1);
				nextPoint.X += 1;
			}
			else if (keyPressed("up"))
			{
				level.getLog().incTurnCounter(1);
				nextPoint.Y -= 1;
			}
			else if (keyPressed("down"))
			{
				level.getLog().incTurnCounter(1);
				nextPoint.Y += 1;
			}
			else
			{
				currHighlight = -1;
				return 0;
			}
			if (level.getCell(nextPoint).getType() == 2)
			{
				level.getLog().addToLog("Found stairs! Press enter to continue.", level.getLog().getTurnCounter(), 0xFFFF00FF);
				level.setStairsFound(true);
			}
			playSound("move.sfs");
			if (level.getCell(nextPoint).getType() == 3)
				playSound("shop.sfs");
			currHighlight = -1;
			movement(level, mover, nextPoint);

			for each (Actor* act in level.getActors())
			{
				movement(level, act, act->move(mover->getLoc()));
			}
		}
		mover->regen();
		return 0;
		break;

	case 2:
		if (keyPressed("1"))
			return 11;
		else if (keyPressed("2"))
			return 12;
		else if (keyPressed("3"))
			return 13;
		else if (keyPressed("escape"))
			return 2;
		break;
	case 3:
		if (keyPressed("return"))
			return 4;
		else if (keyPressed("space"))
			return 5;
		else if (keyPressed("escape"))
			return 2;
		break;
	default: return 0; break;
	}
	return 0;
	
}

void TileLibrary::setScale(int scale)
{
	tl_scale(scale);
}

void TileLibrary::renderString(std::string& inString, Point startPoint)
{
	Point drawPoint = startPoint;
	for (unsigned int i = 0; i < inString.length(); i++)
	{
		if (startPoint.X < getXRes() - 12 && drawPoint.X >= getXRes() - 12)
			break;
		drawTile(inString.at(i), drawPoint);
		drawPoint.X += 1;
	}
}

void TileLibrary::renderLog(MessageLog messageLog)
{
	std::vector<Message> log = messageLog.getLog();
	setScale(2);
	Point drawPoint(0, (getYRes() - 4));
	char* outputI = new char;
	if (hoverMessage.compare("") != 0)
		log.push_back(Message(hoverMessage, messageLog.getTurnCounter(), 0x00FF00FF));
	int size = (int)log.size();
	for (int i = size - 1; i > size - 5; i--)
	{
		if (i >= 0)
		{
			if (log.at(i).getTurn() != messageLog.getTurnCounter())
				color(0x808080FF);
			else
				color(log.at(i).getColor());
			renderString(log.at(i).getText(), drawPoint);
			drawPoint.Y += 1;
			color(0xFFFFFFFF);
		}
	}
	if (hoverMessage.compare("") != 0)
		log.pop_back();
	
	
	setScale(1);
}


void TileLibrary::renderInventory(Player* inPlayer)
{
	int counter = 0;
	setScale(2);

	Point drawPoint(getXRes() - 12, 3);
	for each(Pickup* pickup in inPlayer->getInventory())
	{
		if (pickup->getEquipped())
			color(0x00FFFFFF);
		if (drawPoint == Point(getMouseX(), getMouseY()))
		{
			addItemToHoverMessage(pickup, 1.0);
			currHighlight = counter;
		}
		if (pickup->getDef()->isSpell())
		{
			drawTile(0x31D, drawPoint);
			color(0xFFFFFFF0);
		}
		drawTile(pickup->getTile(), drawPoint);
		color(0xFFFFFFFF);
		drawPoint.X += 1;
		if (drawPoint.X == getXRes())
		{
			drawPoint.X = getXRes() - 12;
			drawPoint.Y += 1;
		}
		counter++;
	}
	setScale(1);
}

int TileLibrary::getMouseX()
{
	return tl_mousex();
}

int TileLibrary::getMouseY()
{
	return tl_mousey();
}

void TileLibrary::color(int inColor)
{
	tl_color(inColor);
}

bool TileLibrary::buttonWentDown(int button = 1)
{
	return tl_buttonwentdown(button);
}

void TileLibrary::renderStats(Player* player)
{
	setScale(2);

	renderStat("LVL: ", player->getLevel(), Point((getXRes() - 12), 0));
	renderStat("HP: ", player->getHP(), "/", player->getMaxHP(), Point((getXRes() - 12), 1));
	renderStat("MP: ", player->getMana(), Point((getXRes() - 12), 2));
	renderStat("GLD: ", player->getGold(), Point((getXRes() - 12), 5));
	renderStat("EXP: ", player->getExp(), Point((getXRes() - 12), 6));
	renderStat("ATT: ", player->getAttack().getNumber(), " d", player->getAttack().getDice(), Point((getXRes() - 12), getYRes() - 6));
	renderStat("BON: ", player->getAttackBonus(), Point((getXRes() - 12), getYRes() - 4));
	renderStat("DEF: ", player->getDefence(), Point((getXRes() - 12), getYRes() - 2));

	setScale(1);
}

void TileLibrary::playSound(char* inFile)
{
	tl_play(inFile);
}

void TileLibrary::renderShop(std::vector<Pickup*> inInv)
{
	int counter = 24;
	setScale(2);

	Point drawPoint(getXRes() - 12, 7);
	for each(Pickup* pickup in inInv)
	{
		if (drawPoint == Point(getMouseX(), getMouseY()))
		{
			addItemToHoverMessage(pickup, 1.5);
			currHighlight = counter;
		}
		if (pickup->getDef()->isSpell())
		{
			drawTile(0x31D, drawPoint);
			color(0xFFFFFFF0);
		}
		drawTile(pickup->getTile(), drawPoint);
		color(0xFFFFFFFF);
		drawPoint.X += 1;
		if (drawPoint.X == getXRes())
		{
			drawPoint.X = getXRes() - 12;
			drawPoint.Y += 1;
		}
		counter++;
	}
	setScale(1);
}


void TileLibrary::addToHoverMessage(std::string inString)
{
	hoverMessage.append(inString);
}

void TileLibrary::addToHoverMessage(std::string inString, int inVal)
{
	char* val = new char;
	hoverMessage.append(inString);
	sprintf_s(val, 10, "%d", inVal);
	hoverMessage.append(val);

}

void TileLibrary::renderStat(std::string inString, int inVal, Point drawPoint)
{
	char* val = new char;
	sprintf_s(val, 10, "%d", inVal);
	inString.append(val);
	renderString(inString, drawPoint);
}

void TileLibrary::renderStat(std::string inString, int inVal1, std::string inSpacer, int inVal2, Point drawPoint)
{
	char* val1 = new char;
	char* val2 = new char;
	sprintf_s(val1, 10, "%d", inVal1);
	sprintf_s(val2, 10, "%d", inVal2);
	inString.append(val1 + inSpacer + val2);
	renderString(inString, drawPoint);
}

void TileLibrary::addItemToHoverMessage(Pickup* pickup, double multiplier)
{
	addToHoverMessage(pickup->getName() + ": " + pickup->getDef()->getDesc());
	if (pickup->getDef()->getType() != 0)
		addToHoverMessage(" DURA: ", pickup->getQuality());
	addToHoverMessage(" VAL: ", (int)((double)pickup->getValue() * multiplier));
	color(0xFFFF00FF);
}