#include "stdafx.h"
#include "TileLibrary.h"



int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	TileLibrary* tl = new TileLibrary();
	tl->initialize("roguelike", 800, 600, "tiles", 32, 3);
	int worldX = 64;
	int worldY = 64;
	World level(worldX, worldY, 100);

	ActorDef* playerDef = new ActorDef(0xC4, "the player", 15, Dice(1, 4), 2, 0);
	Player* player = new Player(playerDef, 20, 0, 0);

	ActorDef* goblin1 = new ActorDef(0xC7, "a goblin warrior", 2, Dice(1, 3), 0, 100);
	ActorDef* goblin2 = new ActorDef(0xC8, "a goblin warrior", 2, Dice(1, 3), 0, 100);
	ActorDef* goblin3 = new ActorDef(0xC9, "a goblin warrior", 3, Dice(1, 4), 0, 100);
	ActorDef* goblin4 = new ActorDef(0xCA, "a goblin warrior", 5, Dice(1, 5), 0, 200);
	ActorDef* goblin5 = new ActorDef(0xCB, "a goblin warrior", 5, Dice(1, 5), 0, 100);
	ActorDef* goblin6 = new ActorDef(0xCC, "a goblin warrior", 7, Dice(2, 2), 0, 100);
	ActorDef* goblin7 = new ActorDef(0xCD, "a goblin shaman", 6, Dice(2, 3), 0, 200);
	ActorDef* goblin8 = new ActorDef(0xCE, "a goblin warrior", 8, Dice(2, 4), 1, 200);
	ActorDef* dog1 = new ActorDef(0x90, "a dog", 10, Dice(1, 6), 0, 200);
	ActorDef* dog2 = new ActorDef(0x91, "a bigger dog", 12, Dice(2, 4), 0, 300);
	ActorDef* ant1 = new ActorDef(0x80, "a giant ant", 8, Dice(1, 2), 2, 300);
	ActorDef* ant2 = new ActorDef(0x83, "a fire ant", 12, Dice(2, 5), 2, 400);
	ActorDef* ant3 = new ActorDef(0x82, "an ant warrior", 18, Dice(3, 4), 3, 500);
	ActorDef* bee1 = new ActorDef(0x81, "a giant bee", 5, Dice(1, 12), 0, 400);
	ActorDef* bee2 = new ActorDef(0x85, "a killer bee", 7, Dice(2, 8), 0, 500);
	ActorDef* cube = new ActorDef(0x88, "a gelatinous cube", 10, Dice(3, 2), 4, 400);
	ActorDef* wolf = new ActorDef(0x95, "a werewolf", 23, Dice(4, 4), 1, 600);
	ActorDef* hound = new ActorDef(0x9A, "a hellhound", 28, Dice(4, 6), 1, 700);
	ActorDef* cerberus = new ActorDef(0x9B, "a cerberus", 45, Dice(6, 6), 1, 900);
	ActorDef* eye = new ActorDef(0x9D, "a flying eye", 8, Dice(3, 5), 0, 500);
	ActorDef* beholder = new ActorDef(0xA1, "a beholder", 30, Dice(3, 12), 1, 800);
	ActorDef* troll = new ActorDef(0xAE, "a troll", 45, Dice(4, 3), 1, 600);
	ActorDef* flayer = new ActorDef(0xB1, "a mind flayer", 25, Dice(5, 4), 2, 700);
	ActorDef* illithid = new ActorDef(0xB2, "an illithid", 27, Dice(5, 5), 3, 800);
	ActorDef* gargoyle = new ActorDef(0xAB, "a gargoyle", 30, Dice(4, 6), 5, 900);
	ActorDef* horror = new ActorDef(0xC3, "a nameless horror", 40, Dice(4, 8), 4, 800);


	std::vector<ActorDef*> actors;
	actors.push_back(goblin1);
	actors.push_back(goblin2);
	actors.push_back(goblin3);
	actors.push_back(goblin4);
	actors.push_back(goblin5);
	actors.push_back(goblin6);
	actors.push_back(goblin7);
	actors.push_back(goblin8);
	actors.push_back(dog1);
	actors.push_back(dog2);
	actors.push_back(ant1);
	actors.push_back(ant2);
	actors.push_back(ant3);
	actors.push_back(bee1);
	actors.push_back(bee2);
	actors.push_back(cube);
	actors.push_back(wolf);
	actors.push_back(hound);
	actors.push_back(cerberus);
	actors.push_back(eye);
	actors.push_back(beholder);
	actors.push_back(troll);
	actors.push_back(flayer);
	actors.push_back(illithid);
	actors.push_back(gargoyle);
	actors.push_back(horror);

	level.setActors(actors);

	PickupDef* potion1 = new PickupDef(0x235, "a perma potion", 0, [&](){player->increaseMaxHP(5); player->setHP(min(player->getMaxHP(), player->getHP() + 5)); }, "MAXHP+5", 1, 0, 200, 0);
	PickupDef* sword1 = new PickupDef(0x250, "a sword", 1, [&](){player->setAttack(Dice(1, 4)); }, "ATT:1 d4", 10, 1, 100, 0);
	PickupDef* potion2 = new PickupDef(0x230, "a health potion", 0, [&](){player->setHP(min(player->getMaxHP(), player->getHP() + 5)); }, "HP+5", 1, 0, 100, 0);
	PickupDef* shield1 = new PickupDef(0x2C0, "a shield", 1, [&](){player->setDefence(player->getDefence() + 1); }, "DEF:1", 10, 2, 200, 0);
	PickupDef* ring1 = new PickupDef(0x330, "a ring", 1, [&](){player->setAttackBonus(player->getAttackBonus() + 2); }, "BON:2", 2, 1, 100, 0);
	PickupDef* spell1 = new PickupDef(0x367, "heal", 2, [&](){player->setHP(min(player->getMaxHP(), player->getHP() + 10)); }, "HP+10", 1, 0, 500, 10);
	PickupDef* spell2 = new PickupDef(0x3C1, "fire sword", 2, [&](){PickupDef* fireSwordDef = new PickupDef(0x3C1, "a fire sword", 1, [&](){player->setAttack(Dice(4, 5)); }, "ATT:4 d5", 5, 1, 200, 0); Pickup* pickup = new Pickup(fireSwordDef); player->addToInventory(pickup); }, "create fire sword", 1, 0, 400, 10);
	PickupDef* potion3 = new PickupDef(0x233, "a mana potion", 0, [&](){player->setMana(player->getMana() + 10); }, "MP+10", 1, 0, 100, 0);
	PickupDef* sword2 = new PickupDef(0x251, "a sword", 1, [&](){player->setAttack(Dice(3, 4)); }, "ATT:3 d4", 5, 1, 300, 0);
	PickupDef* sword3 = new PickupDef(0x252, "a sword", 1, [&](){player->setAttack(Dice(2, 4)); }, "ATT:2 d4", 7, 1, 200, 0);
	PickupDef* shield3 = new PickupDef(0x2C2, "a shield", 1, [&](){player->setDefence(player->getDefence() + 3); }, "DEF:3", 10, 2, 400, 0);
	PickupDef* sword4 = new PickupDef(0x253, "a sword", 1, [&](){player->setAttack(Dice(3, 5)); }, "ATT:3 d5", 4, 1, 375, 0);
	PickupDef* sword5 = new PickupDef(0x254, "a sword", 1, [&](){player->setAttack(Dice(3, 4)); }, "ATT:3 d4", 6, 1, 300, 0);
	PickupDef* potion4 = new PickupDef(0x227, "a health potion", 0, [&](){player->setHP(min(player->getMaxHP(), player->getHP() + 10)); }, "HP+10", 1, 0, 200, 0);
	PickupDef* potion5 = new PickupDef(0x22C, "a perma potion", 0, [&](){player->increaseMaxHP(10); player->setHP(min(player->getMaxHP(), player->getHP() + 10)); }, "HP+5", 1, 0, 400, 0);
	PickupDef* sword6 = new PickupDef(0x255, "a sword", 1, [&](){player->setAttack(Dice(4, 4)); }, "ATT:4 d4", 5, 1, 400, 0);
	PickupDef* sword7 = new PickupDef(0x256, "a sword", 1, [&](){player->setAttack(Dice(5, 3)); }, "ATT:5 d3", 12, 1, 425, 0);
	PickupDef* sword8 = new PickupDef(0x257, "a sword", 1, [&](){player->setAttack(Dice(3, 3)); }, "ATT:3 d3", 9, 1, 250, 0);
	PickupDef* ring3 = new PickupDef(0x332, "a ring", 1, [&](){player->setAttackBonus(player->getAttackBonus() + 4); }, "BON:4", 2, 1, 300, 0);
	PickupDef* ring4 = new PickupDef(0x333, "a ring", 1, [&](){player->setAttackBonus(player->getAttackBonus() + 5); }, "BON:5", 2, 1, 500, 0);
	PickupDef* sword9 = new PickupDef(0x258, "a sword", 1, [&](){player->setAttack(Dice(2, 6)); }, "ATT:2 d6", 7, 1, 300, 0);
	PickupDef* sword10 = new PickupDef(0x259, "a sword", 1, [&](){player->setAttack(Dice(5, 2)); }, "ATT:5 d2", 10, 1, 275, 0);
	PickupDef* sword11 = new PickupDef(0x25A, "a sword", 1, [&](){player->setAttack(Dice(6, 2)); }, "ATT:6 d2", 14, 1, 350, 0);
	PickupDef* potion6 = new PickupDef(0x22A, "a mana potion", 0, [&](){player->setMana(player->getMana() + 15); }, "MP+15", 1, 0, 300, 0);
	PickupDef* potion7 = new PickupDef(0x23A, "a mana potion", 0, [&](){player->setMana(player->getMana() + 20); }, "MP+20", 1, 0, 400, 0);
	PickupDef* potion8 = new PickupDef(0x237, "a health potion", 0, [&](){player->setHP(min(player->getMaxHP(), player->getHP() + 15)); }, "HP+15", 1, 0, 300, 0);
	PickupDef* potion9 = new PickupDef(0x220, "a health potion", 0, [&](){player->setHP(min(player->getMaxHP(), player->getHP() + 20)); }, "HP+20", 1, 0, 400, 0);
	PickupDef* shield2 = new PickupDef(0x2C1, "a shield", 1, [&](){player->setDefence(player->getDefence() + 2); }, "DEF:2", 10, 2, 300, 0);
	PickupDef* shield4 = new PickupDef(0x2C3, "a shield", 1, [&](){player->setDefence(player->getDefence() + 4); }, "DEF:4", 10, 2, 500, 0);
	PickupDef* shield5 = new PickupDef(0x2C4, "a shield", 1, [&](){player->setDefence(player->getDefence() + 5); }, "DEF:5", 10, 2, 600, 0);
	PickupDef* ring2 = new PickupDef(0x331, "a ring", 1, [&](){player->setAttackBonus(player->getAttackBonus() + 3); }, "BON:3", 2, 1, 200, 0);
	PickupDef* ring5 = new PickupDef(0x334, "a ring", 1, [&](){player->setAttackBonus(player->getAttackBonus() + 6); }, "BON:6", 2, 1, 700, 0);
	PickupDef* ring6 = new PickupDef(0x335, "a ring", 1, [&](){player->setAttackBonus(player->getAttackBonus() + 7); }, "BON:7", 2, 1, 900, 0);


	std::vector<PickupDef*> pickups;
	pickups.push_back(potion1);
	pickups.push_back(potion2);
	pickups.push_back(potion3);
	pickups.push_back(potion4);
	pickups.push_back(potion5);
	pickups.push_back(potion6);
	pickups.push_back(potion7);
	pickups.push_back(potion8);
	pickups.push_back(potion9);
	pickups.push_back(sword1);
	pickups.push_back(sword2);
	pickups.push_back(sword3);
	pickups.push_back(sword4);
	pickups.push_back(sword5);
	pickups.push_back(sword6);
	pickups.push_back(sword7);
	pickups.push_back(sword8);
	pickups.push_back(sword9);
	pickups.push_back(sword10);
	pickups.push_back(sword11);
	pickups.push_back(shield1);
	pickups.push_back(shield2);
	pickups.push_back(shield3);
	pickups.push_back(shield4);
	pickups.push_back(shield5);
	pickups.push_back(ring1);
	pickups.push_back(ring2);
	pickups.push_back(ring3);
	pickups.push_back(ring4);
	pickups.push_back(ring5);
	pickups.push_back(ring6);
	pickups.push_back(spell1);
	pickups.push_back(spell2);

	

	level.setPickups(pickups);
	level.generateShop();
	level.generateWorld();
	

	level.loopWorld([&player](Cell inCell)
	{
		if (inCell.getType() == 0)
		{
			inCell.setActor(player);
			player->setLoc(inCell.getPoint());
			return;
		}
	});
	Point playerPoint = player->getLoc();
	int gameState = 2;
	while (true)
	{
		tl->frameStart(0);
		tl->frameRender(level, player, gameState);
		tl->renderLog(level.getLog());
		if (tl->keyPressed("escape"))
		{
			tl->shutDown();
			break;
		}
		PickupDef* startSkillDef;
		Pickup* startSkill;
		switch(tl->playerInput(level, player, gameState))
		{
		case 11:
			playerDef = new ActorDef(0xC4, "the player", 10, Dice(1, 3), 0, 0);
			player = new Player(playerDef, 30, 1, 0);
			startSkillDef = new PickupDef(0x3B4, "arcane arrow", 2, [&](){for each(Actor* actor in level.getActors()){ if ((Point(player->getLoc() - actor->getLoc()).getVectorDist() <= 4) && level.lineOfSight(player->getLoc(), Point(player->getLoc() - actor->getLoc())))level.getLog().addToLog(actor->attack(player->getLevel()), level.getLog().getTurnCounter(), 0xFFFFFFFF); } }, "DMG: LVL", 1, 0, 0, 7);
			startSkill = new Pickup(startSkillDef);
			player->addToInventory(startSkill);
			player->setLoc(playerPoint);
			gameState = 1;
			tl->playSound("start.sfs");
			break;
		case 12:
			playerDef = new ActorDef(0xAC, "the player", 15, Dice(1, 6), 1, 0);
			player = new Player(playerDef, 12, 0, 0);
			startSkillDef = new PickupDef(0x266, "vorpal blade", 2, [&](){PickupDef* poisonedDaggerDef = new PickupDef(0x266, "vorpal blade", 1, [&](){player->setAttack(Dice(player->getLevel(), 8)); }, "ATT:LVL d8", 1, 1, 0, 0); Pickup* pickup = new Pickup(poisonedDaggerDef); player->addToInventory(pickup); player->equip(pickup); }, "draw vorpal blade", 1, 0, 0, 4);
			startSkill = new Pickup(startSkillDef);
			player->addToInventory(startSkill);
			player->setLoc(playerPoint);
			gameState = 1;
			tl->playSound("start.sfs");
			break;
		case 13:
			playerDef = new ActorDef(0xAF, "the player", 20, Dice(2, 3), 2, 0);
			player = new Player(playerDef, 5, 0, 0);
			startSkillDef = new PickupDef(0x362, "whirlwind", 2, [&](){
				for each(Actor* actor in level.getActors()){
					if (Point(player->getLoc() - actor->getLoc()).getVectorDist() == 1)
						level.getLog().addToLog(actor->attack(player->getDamage()), level.getLog().getTurnCounter(), 0xFFFFFFFF);
				}

			}, "ATT adjacent", 1, 0, 0, 0);
			startSkill = new Pickup(startSkillDef);
			player->addToInventory(startSkill);
			player->setLoc(playerPoint);
			gameState = 1;
			tl->playSound("start.sfs");
			break;
		case 5:
			gameState = 1;
			break;
		case 4:
			level.cleanUp(player);
			level = World(worldX, worldY, 100, actors, pickups);
			while (true)
			{
				int randX = rand() % worldX;
				int randY = rand() % worldY;
				Point randPoint(randX, randY);
				if (level.getCell(randPoint).getType() == 0)
				{
					playerPoint = randPoint;
					break;
				}
			}
			player->setLoc(Point(0,0));
			gameState = 2;
			break;
		case 3:
			gameState = 3;
			break;
		case 2:
			level.cleanUp(player);
			tl->shutDown();
			break;
		case 1:
			player->cleanUp();
			level.cleanUp(player);
			level = World(worldX, worldY, level.getDifficulty() + 50, actors, pickups);
			while (true)
			{
				int randX = rand() % worldX;
				int randY = rand() % worldY;
				Point randPoint(randX, randY);
				if (level.getCell(randPoint).getType() == 0)
				{
					player->setLoc(randPoint);
					break;
				}	
			}
			break;
		case 0:
			player->cleanUp();
			level.cleanUp(player);
			break;
		}
	}
		
}