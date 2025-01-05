#include "Mapp.h"

Mapp::~Mapp() {		
	mapp.clear();
}

void Mapp::Initzialize()
{
	LvL0();
}

void Mapp::ResetLvL()
{
	LoadLvL();
}

void Mapp::LvLFinished() {
	mapp.clear();

	lvl++;
	ResetLvL();
}

void Mapp::LoadLvL() {
	switch (lvl) {
	case 0: LvL0(); break;
	case 1: LvL1(); break;
	case 2: LvL2(); break;
	default: GameWon(); break;
	}
}

void Mapp::GameWon() {
	*runningPtr = false;
}

void Mapp::LvL0()
{
	// clear up before writing to prevent memory leaks
	mapp.clear();

	// set size
	mapp.resize(width, std::vector<char>(hight, NULL)); // restucturing code to have Block() be the actual blocks and the empty positions being nullptr would remove a bunch of releases and speed up efichency however needs a late restructuring of code	

	// set the mapp
			// setting blocks to already Block initialized positions causes memory leaks and requires first deliting the current block
	// floor
	for (int x = 0; x < width; x++) {
		mapp[x][16] = BlockManager::ground; //new Block('=', Text::Green, true);
	}
	// platform
	for (int x = 8; x < 12; x++) {
		mapp[x][13] = BlockManager::ground; //new Block('=', Text::Green, true);
	}
	//lone block
	mapp[3][15] = BlockManager::ground; // new Block('=', Text::Green, true);

	/*flag*/for (short y = 11; y < 16; y++) {
		mapp[width - 1][y] = BlockManager::flagPole; //new FlagPole();
	} mapp[width - 1][10] = BlockManager::flag; 
}

void Mapp::LvL1()
{
	LvLFinished();
}

void Mapp::LvL2()
{
	LvLFinished();
}