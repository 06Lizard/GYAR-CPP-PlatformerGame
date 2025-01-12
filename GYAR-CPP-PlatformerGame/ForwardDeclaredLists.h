#pragma once
#include <thread>
#include <vector>
#include <chrono>
#include <conio.h> // allows for _getch witch waits for keypress
#include "LvLManager.h"
#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Enemy1.h"

struct LvLManager::ForwardDeclaredLists {
public:
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::unique_ptr<Projectile>> projectiles;

	ForwardDeclaredLists() = default;
	~ForwardDeclaredLists() = default;
	void Clear() {
		enemies.clear();
		projectiles.clear();
	}
};