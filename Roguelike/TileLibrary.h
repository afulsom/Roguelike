#include "stdafx.h"
#include "World.h"

class TileLibrary
{
private:
	int currHighlight;
	std::string hoverMessage;
public:
	TileLibrary();
	~TileLibrary();
	void drawTile(int, Point);
	void drawTile(char, Point);
	bool keyPressed(char*);
	void frameStart(int);
	int getXRes();
	int getYRes();
	void initialize(char*, int, int, char*, int, int);
	void shutDown();
	void frameRender(World&, Player*, int);
	void movement(World&, Actor*, Point);
	void setScale(int);
	void renderString(std::string&, Point);
	void renderLog(MessageLog);
	int playerInput(World&, Player*, int);
	void renderInventory(Player*);
	int getMouseX();
	int getMouseY();
	void color(int);
	bool buttonWentDown(int);
	void renderStats(Player*);
	void playSound(char*);
	void renderShop(std::vector<Pickup*>);
	void addToHoverMessage(std::string);
	void addToHoverMessage(std::string, int);
	void addItemToHoverMessage(Pickup*, double);
	void renderStat(std::string, int, Point);
	void renderStat(std::string, int, std::string, int, Point);
};