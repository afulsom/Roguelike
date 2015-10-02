#include "stdafx.h"
#include "Player.h"
#include "Monster.h"

class Cell
{
private:
	int tileType;
	int tileNumber;
	int accentNumber;
	Point cellPoint;
	int zone;
	Actor* currActor;
	Pickup* currPickup;
	bool fog;
public:
	Cell();
	Cell(int, int);
	Cell(int, int, int, int);
	Cell(int, int, Point);
	Cell(int, int, int, int, int);
	Cell(int, int, Point, int);
	Cell(const Cell&);
	Cell operator=(const Cell&);
	~Cell();
	int getType() const;
	int getNumber() const;
	void setType(int);
	void setNumber(int);
	Point getPoint() const;
	void setPoint(Point&);
	int getZone() const;
	void setZone(int);
	void setActor(Actor*);
	Actor* getActor() const;
	void setPickup(Pickup*);
	Pickup* getPickup() const;
	int getAccent() const;
	void setAccent(int);
	void deFog();
	bool getFog() const;
};
