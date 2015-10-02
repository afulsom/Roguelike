#include "Cell.h"


Cell::Cell()
{
	tileNumber = 0;
	tileType = 0;
	cellPoint.X = 0;
	cellPoint.Y = 0;
	zone = 0;
	currActor = nullptr;
	currPickup = nullptr;
	accentNumber = 0;
	fog = true;
}

Cell::Cell(int inType, int inNumber)
{
	tileType = inType;
	tileNumber = inNumber;
	cellPoint.X = 0;
	cellPoint.Y = 0;
	zone = 0;
	currActor = nullptr;
	currPickup = nullptr;
	accentNumber = 0;
	fog = true;
}

Cell::Cell(int inType, int inNumber, int inX, int inY)
{
	tileType = inType;
	tileNumber = inNumber;
	cellPoint.X = inX;
	cellPoint.Y = inY;
	zone = 0;
	currPickup = nullptr;
	currActor = nullptr;
	accentNumber = 0;
	fog = true;
}

Cell::Cell(int inType, int inNumber, Point inPoint)
{
	tileType = inType;
	tileNumber = inNumber;
	cellPoint = inPoint;
	zone = 0;
	currPickup = nullptr;
	currActor = nullptr;
	accentNumber = 0;
	fog = true;
}

Cell::Cell(int inType, int inNumber, int inX, int inY, int inZone)
{
	tileType = inType;
	tileNumber = inNumber;
	cellPoint.X = inX;
	cellPoint.Y = inY;
	zone = inZone;
	currPickup = nullptr;
	currActor = nullptr;
	accentNumber = 0;
	fog = true;
}

Cell::Cell(int inType, int inNumber, Point inPoint, int inZone)
{
	tileType = inType;
	tileNumber = inNumber;
	cellPoint = inPoint;
	zone = inZone;
	currPickup = nullptr;
	currActor = nullptr;
	accentNumber = 0;
	fog = true;
}

Cell::Cell(const Cell& inCell)
{
	tileType = inCell.getType();
	tileNumber = inCell.getNumber();
	cellPoint = inCell.getPoint();
	zone = inCell.getZone();
	currActor = inCell.getActor();
	currPickup = inCell.getPickup();
	accentNumber = inCell.getAccent();
	fog = inCell.getFog();
}

Cell Cell::operator=(const Cell& inCell)
{
	tileType = inCell.getType();
	tileNumber = inCell.getNumber();
	cellPoint = inCell.getPoint();
	zone = inCell.getZone();
	currActor = inCell.getActor();
	currPickup = inCell.getPickup();
	accentNumber = inCell.getAccent();
	fog = inCell.getFog();
	return *this;
}

Cell::~Cell()
{

}

int Cell::getType() const
{
	return tileType;
}

int Cell::getNumber() const
{
	return tileNumber;
}

void Cell::setNumber(int inNumber)
{
	tileNumber = inNumber;
}

void Cell::setType(int inType)
{
	tileType = inType;
}

Point Cell::getPoint() const
{
	return cellPoint;
}

void Cell::setPoint(Point &inPoint)
{
	cellPoint = Point(inPoint);
}

int Cell::getZone() const
{
	return zone;
}

void Cell::setZone(int inZone)
{
	zone = inZone;
}

void Cell::setActor(Actor* inActor)
{
	currActor = inActor;
}

Actor* Cell::getActor() const
{
	return currActor;
}

void Cell::setPickup(Pickup* inPickup)
{
	currPickup = inPickup;
}

Pickup* Cell::getPickup() const
{
	return currPickup;
}

int Cell::getAccent() const
{
	return accentNumber;
}

void Cell::setAccent(int inAccent)
{
	accentNumber = inAccent;
}

void Cell::deFog()
{
	fog = false;
}

bool Cell::getFog() const
{
	return fog;
}