#pragma once
#include <vector>
#include "Entity.h"
#include "BlockManager.h"

class Enemy : public Entity {
protected:
	const LvLManager::LvLManagerHandle& _LvLManagerHandle;

public:
	Enemy(short HP, char texture, short colour, bool collision, short x, short y, bool faceRight, const LvLManager::LvLManagerHandle& _LvLManagerHandle)
		//: Entity(1, 'E', 93, x, y)
		: Entity(HP, texture, colour, collision, x, y), _LvLManagerHandle(_LvLManagerHandle)
	{
		if (faceRight) states &= Right; 
	}

	virtual ~Enemy() = default;

	virtual void Update() = 0;

protected:
	virtual void Move() = 0;
};
