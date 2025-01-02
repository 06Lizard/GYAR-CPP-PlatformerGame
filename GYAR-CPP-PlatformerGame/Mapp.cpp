#include "Mapp.h"
#include <iostream>
Mapp::~Mapp() {	
	ClearMapp();
	mapp.clear();
}

void Mapp::Start()
{
	LvL0();
}

void Mapp::ResetLvL()
{
	LoadLvL();
}

void Mapp::LvLFinished() {
	//ClearMapp();

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
	//ClearMapp();

	// set size
	mapp.resize(width, std::vector<Block*>(hight, new Block())); // restucturing code to have Block() be the actual blocks and the empty positions being nullptr would remove a bunch of releases and speed up efichency however needs a late restructuring of code	

	// set the mapp
		// setting blocks to already Block initialized positions causes memory leaks and requires first deliting the current block
	// floor
	for (int x = 0; x < width; x++) {
		mapp[x][16] = new Block('=', Text::Green, true);
	}
	// platform
	for (int x = 8; x < 12; x++) {
		mapp[x][13] = new Block('=', Text::Green, true);
	}
	//lone block
	mapp[3][15] = new Block('=', Text::Green, true);

	/*flag*/for (short y = 11; y < 16; y++) {
		mapp[width - 1][y] = new FlagPole();
	}
}

void Mapp::LvL1()
{
	LvLFinished();
}

void Mapp::LvL2()
{
	LvLFinished();
}

void Mapp::ClearMapp() {
	// memory leaks iminent
}