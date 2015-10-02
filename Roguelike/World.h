#include "stdafx.h"
#include "Cell.h"
#include "MessageLog.h"

class World
{
private:
	int xSize;
	int ySize;
	std::vector<std::vector<Cell>> worldArray;
	std::vector<Actor*> actorArray;
	std::vector<ActorDef*> actorDefArray;
	std::vector<PickupDef*> pickupArray;
	Cell* dummyCell;
	MessageLog log;
	int grass = 0x100;
	int floor = 0x127;
	int damagedFloor = 0x137;
	int wall = 0x14D;
	int stairs = 0x12C;
	int shop = 0x199;
	int difficulty;
	std::vector<Pickup*> shopInv;
	bool stairsFound;
public:
	World();
	World(int, int, int);
	World(int, int, int, std::vector<ActorDef*>, std::vector<PickupDef*>);
	~World();
	void generateWorld();
	int getType(Point);
	int getNumber(Point);
	Cell& getCell(Point);
	void loop_xy(Point, Point, std::function<void(Cell&)>);
	void loopWorld(std::function<void(Cell&)>);
	void findLargestZone();
	int floodFill(Cell&, int);
	void setActors(std::vector<ActorDef*>);
	void placeActors();
	void cleanUp(Player*);
	MessageLog& getLog();
	std::vector<Actor*>& getActors();
	void setPickups(std::vector<PickupDef*>);
	std::vector<PickupDef*>& getPickups();
	int getDifficulty();
	template <class T> T* pickFromTable(std::vector<T*> table);
	std::vector<Pickup*> getShopInv();
	void addToShop(Pickup*);
	void removeFromShop(int);
	void setShopInv(std::vector<Pickup*>);
	void generateShop();
	bool lineOfSight(Point, Point);
	void deFoW(Point, int);
	bool lineOfSightDeFog(Point, Point);
	bool areStairsFound();
	void setStairsFound(bool);
	void placePoI(int, int);
};