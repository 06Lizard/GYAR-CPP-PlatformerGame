#pragma once
#include "BlockManager.h"
#include <vector>
// we have a SLIGHT chance of RACE CONDITIONS witht his mapp.
// everyone can say the lvl was finished :/

class Mapp
{	
private:
	int TMP = 0;
	bool* runningPtr;
	short lvl;
public:
	static const short width = 64;
	static const short hight = 32;	
	//Block* mapp[width][hight]; // 4096bytes to store the map...
	std::vector<std::vector<char>> mapp; // 2D vector of Block identifiers

public:
	Mapp(bool* running) : runningPtr(running), lvl(0) { Initzialize(); }
	~Mapp();
	void Initzialize();
	void ResetLvL();	
	void LvLFinished();
	short getLvL() { return lvl; }

private:
	void LoadLvL();
	void GameWon();
	void LvL0();
	void LvL1();
	void LvL2();	
};