#pragma once
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
};