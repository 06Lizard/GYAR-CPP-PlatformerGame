#pragma once
#include <vector>
#include <functional>
#include <memory>
#include <iostream>
#include "BlockManager.h"
#include "Position.h"

class Player;
class Enemy;
class Enemy1;
class Projectile;

// we have a SLIGHT chance of RACE CONDITIONS witht his mapp.
// everyone can say the lvl was finished :/

class LvLManager
{	
public:
	// nested MappHandle allowing limited acses to enemies and projectiles
	class LvLManagerHandle {
	private:
		std::function<void(short, short, bool)> createProjectileCallBack;

	public:
		const std::vector<std::vector<char>>& mapp; // direct acses ti mapp

		// constructor 
		LvLManagerHandle(const std::vector<std::vector<char>>& mappData,
				std::function<void(short, short, bool)> projectileCallBack)
			: mapp(mappData), createProjectileCallBack(projectileCallBack) {}

		// spawn a projectile
		void createProjectile(short x, short y, bool facingRight) {
			if (createProjectileCallBack) {
				createProjectileCallBack(x, y, facingRight);
			}
		}		
	};

private:
	LvLManagerHandle handle;

	int TMP = 0;
	bool& runningPtr;
	Position& cameraPos;
	Player& player;
	short lvl;

public:
	static const short screenWidth = 32;
	static const short screenHight = 16;
	static const short width = 64;
	static const short hight = 32;		

	// making the forward declaed class lists uniqe ptr becuse icbbam
	struct ForwardDeclaredLists;
	std::unique_ptr<ForwardDeclaredLists> entitiesList;
	std::vector<std::vector<char>> mapp; // 2D vector of Block identifiers
	// list of type entity to store enemies as they all derive from that

public:
	LvLManager(bool& running, Position& cameraPos, Player& player);
	~LvLManager();

	void Initzialize();
	void ResetLvL();	
	void LvLFinished();
	void Update();
	void Render();

	short getLvL() { return lvl; }
	void addEnemy(std::unique_ptr<Enemy> enemy);
	void addProjectile(short x, short y, bool isRight);

	LvLManagerHandle& getHandle() {
		return handle;
	}

private:
	void LoadLvL();
	void GameWon();
	void LvL0();
	void LvL1();
	void LvL2();
};