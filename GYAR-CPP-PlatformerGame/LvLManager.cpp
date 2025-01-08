//#include "LvLManager.h"
//#include "Projectile.h"
//#include "Enemy.h"
//#include "Enemy1.h"
#include "ForwardDeclaredLists.h"

//struct LvLManager::ForwardDeclaredLists {
//public:
//	std::vector<std::unique_ptr<Enemy>> enemies;
//	std::vector<std::unique_ptr<Projectile>> projectiles;
//
//	ForwardDeclaredLists() = default;
//	~ForwardDeclaredLists() = default;
//};

LvLManager::LvLManager(bool* running, Position* cameraPos)
	: runningPtr(running), cameraPos(cameraPos), lvl(0), entitiesList(std::make_unique<ForwardDeclaredLists>()),
	handle(mapp, [this](short x, short y, bool facingRight) { addProjectile(x, y, facingRight);	}) 
{
	Initzialize();
}

LvLManager::~LvLManager() = default;

void LvLManager::Initzialize()
{
	LvL0();
}

void LvLManager::ResetLvL()
{
	LoadLvL();
}

void LvLManager::LvLFinished() {
	lvl++;
	ResetLvL();
}

void LvLManager::Update() {
	// only update enemies on the screen
	for (auto& enemy : entitiesList->enemies)
	{
		auto x = enemy->x;
		auto y = enemy->y;

		if (cameraPos->x <= x && x < cameraPos->x + screenWidth &&
			cameraPos->y <= y && y < cameraPos->y + screenHight) {
			enemy->Update();  // polymorphic call
		}
	}
	// always update projectile, it has it's own lifetime logic
	for (auto& projectile : entitiesList->projectiles)
	{
		projectile->Update();
	}
}

void LvLManager::Render() {
	for (auto& enemy : entitiesList->enemies)
	{
		auto x = enemy->x;
		auto y = enemy->y;

		// x < camraPos->x+screenWidth
		// x > camraPos->x;

		if (cameraPos->x <= x && x < cameraPos->x + screenWidth &&
			cameraPos->y <= y && y < cameraPos->y + screenHight && !mapp[x][y]) {
			std::cout << "\033[" << y-cameraPos->y + 1 << ";" << x-cameraPos->x + 1 << "H\033[" << enemy->getColour() << "m" << enemy->getTexture();
		}
	}
	for (auto& projectile : entitiesList->projectiles)
	{
		auto x = projectile->x;
		auto y = projectile->y;

		if (cameraPos->x <= x && x < cameraPos->x + screenWidth &&
			cameraPos->y <= y && y < cameraPos->y + screenHight && !mapp[x][y]) {
			std::cout << "\033[" << y + 1 << ";" << x + 1 << "H\033[" << projectile->getColour() << "m" << projectile->getTexture();
		}
	}
}

void LvLManager::addEnemy(std::unique_ptr<Enemy> enemy) {
	entitiesList->enemies.push_back(std::move(enemy));
}

void LvLManager::addProjectile(short x, short y, bool isRight) {
	entitiesList->projectiles.push_back(std::make_unique<Projectile>(x, y, isRight, getHandle()));
}

void LvLManager::LoadLvL() {
	switch (lvl) {
	case 0: LvL0(); break;
	case 1: LvL1(); break;
	case 2: LvL2(); break;
	default: GameWon(); break;
	}
}

void LvLManager::GameWon() {
	*runningPtr = false;
}

void LvLManager::LvL0()
{
	// clear up before writing to prevent memory leaks
	mapp.clear();

	// set size
	mapp.resize(width, std::vector<char>(hight, NULL)); // restucturing code to have Block() be the actual blocks and the empty positions being nullptr would remove a bunch of releases and speed up efichency however needs a late restructuring of code	

	// set the mapp
	
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

	// set the enemies			
	addEnemy(std::make_unique<Enemy1>(5, 5, false, getHandle()));	
}

void LvLManager::LvL1()
{
	LvLFinished();
}

void LvLManager::LvL2()
{
	LvLFinished();
}