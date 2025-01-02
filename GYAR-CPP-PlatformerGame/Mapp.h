#pragma once
#include "Block.h"
#include "Flag.h"
#include <vector>
//#include <memory>
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
	std::vector<std::vector<Block*>> mapp; // 2D vector of Blocks
	//std::vector<std::vector<std::unique_ptr<Block>>> mapp; // 2D vector of Blocks
	// make uniqe ptr and remove the Block() or make it into the filled block wehere block type empty will be removed everywhere and replaced with nullptr
	// this also requires remaking render again

public:
	Mapp(bool* running) : runningPtr(running), lvl(0) { Start(); }
	~Mapp();
	void Start();
	void ResetLvL();	
	void LvLFinished();

private:
	void LoadLvL();
	void GameWon();
	void LvL0();
	void LvL1();
	void LvL2();
	void ClearMapp();
};