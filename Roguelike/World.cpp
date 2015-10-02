#include "World.h"


World::World()
{
	xSize = 64;
	ySize = 64;
	dummyCell = new Cell(1, 0x100);
	stairsFound = false;
}

World::World(int x, int y, int inDifficulty)
{
	xSize = x;
	ySize = y;
	dummyCell = new Cell(1, grass);
	difficulty = inDifficulty;
	stairsFound = false;
}

World::World(int x, int y, int inDifficulty, std::vector<ActorDef*> actors, std::vector<PickupDef*> pickups)
{
	xSize = x;
	ySize = y;
	dummyCell = new Cell(1, grass);
	difficulty = inDifficulty;
	stairsFound = false;
	setActors(actors);
	setPickups(pickups);
	generateShop();
	generateWorld();
}

World::~World()
{

}

void World::generateWorld()
{
	for (int i = 0; i < xSize; i++)
	{
		worldArray.push_back(std::vector<Cell>(ySize));
		for (int j = 0; j < ySize; j++)
		{
			worldArray[i][j] = Cell(1, grass, Point(i, j));
		}
	}

	
	for (int i = 0; i < 200; i++)
	{
		int xCoord = (rand() % (xSize-14)) + 6;
		int yCoord = (rand() % (ySize-14)) + 6;
		int xDim = (rand() % 4) + 2;
		int yDim = (rand() % 4) + 2;

		loop_xy(Point(xCoord - (xDim / 2), yCoord - (yDim / 2)), Point(xDim, yDim), [&](Cell& inCell)
		{
			inCell.setNumber(floor);
			inCell.setType(0);
		});
	}

	findLargestZone();



	
	loopWorld([&](Cell& inCell)
	{
		bool isAdjacent = false;
		if (inCell.getType() == 1)
		{
			
			if (getCell(inCell.getPoint() + Point(1, 0)).getType() == 0)
			{
				isAdjacent = true;
			}
			else if (getCell(inCell.getPoint() + Point(0, 1)).getType() == 0)
			{
				isAdjacent = true;
			}
			else if (getCell(inCell.getPoint() + Point(-1, 0)).getType() == 0)
			{
				isAdjacent = true;
			}
			else if (getCell(inCell.getPoint() + Point(0, -1)).getType() == 0)
			{
				isAdjacent = true;
			}
		}
		if (isAdjacent)
		{
			inCell.setType(1);
			inCell.setNumber(wall);
		}
			
		
	});

	placePoI(2, stairs);
	placePoI(3, shop);
	placeActors();
}

void World::loop_xy(Point pos, Point sz, std::function<void (Cell&)> f)
{
	for (int i = 0; i < sz.X; i++)
	{
		for (int j = 0; j < sz.Y; j++)
		{
			Point tempPoint = Point(pos.X + i, pos.Y + j);
			if (tempPoint.X < 0 || tempPoint.Y < 0 || tempPoint.X > xSize - 1 || tempPoint.Y > ySize - 1)
			{
				dummyCell->setPoint(tempPoint);
				f(*dummyCell);
			}
			else
				f(getCell(tempPoint));
		}
	}
}

void World::loopWorld(std::function<void(Cell&)> f)
{
	loop_xy(Point(0, 0), Point(xSize, ySize), f);
}

Cell& World::getCell(Point inPoint)
{
	if (inPoint.X < 0 || inPoint.Y < 0 || inPoint.X >= xSize || inPoint.Y >= ySize)
	{
		dummyCell->setPoint(inPoint);
		return *dummyCell;
	}
	return worldArray[inPoint.X][inPoint.Y];
}

int World::getType(Point inPoint)
{
	return getCell(inPoint).getType();
}

int World::getNumber(Point inPoint)
{
	return getCell(inPoint).getNumber();
}

void World::findLargestZone()
{
	int currZone = 1;
	int maxSize = 0;
	int maxZone = 1;
	loopWorld([&](Cell& inCell)
	{
		if (inCell.getType() == 0 && inCell.getZone() == 0)
		{
			int tempZone = floodFill(inCell, currZone);
			if (tempZone > maxSize)
			{
				maxSize = tempZone;
				maxZone = currZone;
			}
			currZone++;
		}
		
	});

	loopWorld([&](Cell& inCell)
	{
		if (inCell.getZone() == maxZone)
		{
			inCell.setType(0);
			int tileChance = rand() % 10;
			if (tileChance < 8)
				inCell.setNumber(floor);
			else
				inCell.setNumber(damagedFloor);
		}
		else
		{
			inCell.setType(1);
			inCell.setNumber(grass);
		}
	});


}

int World::floodFill(Cell& inCell, int inZone)
{
	int fill1 = 0, fill2 = 0, fill3 = 0, fill4 = 0;
	if (inCell.getType() == 0 && inCell.getZone() == 0)
	{
		inCell.setZone(inZone);
		inCell.setType(1);
		Point inPoint = inCell.getPoint();
		fill1 = floodFill(getCell(Point(inPoint) + Point(1, 0)), inZone);
		fill2 = floodFill(getCell(Point(inPoint) + Point(0, 1)), inZone);
		fill3 = floodFill(getCell(Point(inPoint) + Point(-1, 0)), inZone);
		fill4 = floodFill(getCell(Point(inPoint) + Point(0, -1)), inZone);
	}
	else
		return 0;
	return 1 + fill1 + fill2 + fill3 + fill4;
}

void World::setActors(std::vector<ActorDef*> actors)
{
	actorDefArray = actors;
	
}

void World::placeActors()
{
	loopWorld([&](Cell& inCell)
	{

			if (inCell.getType() == 0)
			{
				int spawnChance = rand() % 50;
				if (spawnChance == 0)
				{
					Actor* act = new Monster(pickFromTable(actorDefArray));
					actorArray.push_back(act);
					act->setLoc(inCell.getPoint());
					act->setHome(inCell.getPoint());
					inCell.setActor(act);

					int pickupChance = rand() % 3;
					if (pickupChance == 0)
					{
						Pickup* pickup = new Pickup(pickFromTable(pickupArray));
						pickup->setLoc(inCell.getPoint());
						inCell.setPickup(pickup);
					}
				}
			}
	});
}

void World::cleanUp(Player* player)
{
	loopWorld([&](Cell& inCell)
	{
		if (inCell.getActor() == nullptr)
			return;
		if (inCell.getActor()->getHP() <= 0)
		{
			log.addToLog(inCell.getActor()->die(), log.getTurnCounter(), 0xFF0000FF);
			int counter = 0;
			for each (Actor* act in actorArray)
			{
				if (act == inCell.getActor())
				{
					player->setExp(player->getExp() + (act->getDefinition()->getDifficulty() / 5));
					actorArray.erase(actorArray.begin() + counter);
					delete act;
					break;
				}
				counter++;
					
			}
			inCell.setActor(nullptr);
		}
	});
}

MessageLog& World::getLog()
{
	return log;
}

std::vector<Actor*>& World::getActors()
{
	return actorArray;
}

void World::setPickups(std::vector<PickupDef*> pickups)
{
	pickupArray = pickups;

}

std::vector<PickupDef*>& World::getPickups()
{
	return pickupArray;
}

int World::getDifficulty()
{
	return difficulty;
}

template<class T> T* World::pickFromTable(std::vector<T*> table)
{
	int freqSum = 0;
	double freq = 0;
	for each (T* element in table)
	{
		freqSum += (int)(element->getDifficulty(difficulty));
	}
	int tableLoc = rand() % freqSum;
	int findSum = 0;
	for each (T* element in table)
	{
		if (findSum <= tableLoc && findSum + (int)element->getDifficulty(difficulty) > tableLoc)
		{
			return element;
		}
		findSum += (int)element->getDifficulty(difficulty);
		
	}
	return nullptr;

}

std::vector<Pickup*> World::getShopInv()
{
	return shopInv;
}

void World::setShopInv(std::vector<Pickup*> inInv)
{
	shopInv = inInv;
}

void World::addToShop(Pickup* inPick)
{
	shopInv.push_back(inPick);
}

void World::removeFromShop(int index)
{
	shopInv.erase(shopInv.begin() + index);
}

void World::generateShop()
{
	for (int i = 0; i < 5; i++)
	{
		Pickup* pickup = new Pickup(pickFromTable(pickupArray));
		addToShop(pickup);
	}
	
}

bool World::lineOfSight(Point playerPoint, Point destVector)
{
	Point destPoint = Point(playerPoint + destVector);
	int xDiff = playerPoint.X - destPoint.X;
	int yDiff = playerPoint.Y - destPoint.Y;
	double slopeRemainder = 0;
	double slope = abs((0.0 + yDiff) /  (0.0 + xDiff));
	int x = playerPoint.X;
	int y = playerPoint.Y;
	if (xDiff == 0)
	{
		for (int i = 0; i < abs(yDiff); i++)
		{
			y += helper::sign(yDiff);
			if (getCell(Point(x, y)).getType() == 1)
				return false;
		}
	}
	else
	{
		for (int i = 0; i < abs(xDiff); i++)
		{
			x += helper::sign(xDiff);
			if (getCell(Point(x, y)).getType() == 1)
				return false;
			slopeRemainder += slope;
			while (slopeRemainder >= 0.5)
			{
				y += helper::sign(yDiff);
				slopeRemainder -= 1.0;
				if (getCell(Point(x, y)).getType() == 1)
					return false;
			}
		}
	}
	return true;
}

bool World::lineOfSightDeFog(Point playerPoint, Point destVector)
{
	std::vector<Cell> path;
	Point destPoint = Point(playerPoint.X + destVector.X, playerPoint.Y + destVector.Y);
	int xDiff = playerPoint.X - destPoint.X;
	int yDiff = playerPoint.Y - destPoint.Y;
	double slopeRemainder = 0;
	double slope = abs((double)yDiff / (double)xDiff);
	int x = playerPoint.X;
	int y = playerPoint.Y;
	if (xDiff == 0)
	{
		for (int i = 0; i < abs(yDiff); i++)
		{
			y += -1 * helper::sign(yDiff);
			getCell(Point(x, y)).deFog();
			if (getCell(Point(x, y)).getType() == 1)
				return false;
			path.push_back(getCell(Point(x, y)));
		}
	}
	else
	{
		for (int i = 0; i < abs(xDiff); i++)
		{
			x += -1 * helper::sign(xDiff);
			getCell(Point(x, y)).deFog();
			if (getCell(Point(x, y)).getType() == 1)
				return false;
			path.push_back(getCell(Point(x, y)));
			slopeRemainder += slope;
			while (slopeRemainder >= 0.5)
			{
				y += -1 * helper::sign(yDiff);
				slopeRemainder -= 1.0;
				getCell(Point(x, y)).deFog();
				if (getCell(Point(x, y)).getType() == 1)
					return false;
				path.push_back(getCell(Point(x, y)));
			}
		}
	}
	return true;
}

void World::deFoW(Point playerPoint, int radius)
{
	double pi = 3.14159265359;
	std::vector<Point*> destArray;
	for (double i = 0; i < 2; i += .1)
	{
		double y = sin(i*pi) * radius;
		double x = cos(i*pi) * radius;
		Point* destPoint = new Point((int)x, (int)y);
		bool isInArray = false;
		for each (Point* point in destArray)
		{
			if (point->X == destPoint->X && point->Y == destPoint->Y)
			{
				isInArray = true;
				break;
			}
		}
		if (!isInArray)
			destArray.push_back(destPoint);
	}
	for each (Point* point in destArray)
	{
		getCell(playerPoint).deFog();
		Point realPoint = Point(playerPoint.X + point->X, playerPoint.Y + point->Y);
		lineOfSightDeFog(playerPoint, *point);
	}
	for each(Point* point in destArray)
	{
		delete point;
	}
}

bool World::areStairsFound()
{
	return stairsFound;
}

void World::setStairsFound(bool inStatus)
{
	stairsFound = inStatus;
}

void World::placePoI(int type, int number)
{
	while (true)
	{
		int xRand = rand() % 64;
		int yRand = rand() % 64;
		if (worldArray[xRand][yRand].getType() == 0)
		{
			worldArray[xRand][yRand].setType(type);
			worldArray[xRand][yRand].setAccent(number);
			break;
		}
	}
}