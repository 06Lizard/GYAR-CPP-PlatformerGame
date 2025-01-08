#pragma once
#include "Enemy.h"

class Enemy1 : public Enemy
{
private:
	static const short _health = 1;
	static const char _texture = 'E';
	static const int _colour = Text::BrightYellow;
	static const bool _collision = false;

public:
	Enemy1(short x, short y, bool faceRight, const LvLManager::LvLManagerHandle& _LvLManagerHandle)	
		//: Entity(1, 'E', 93, x, y)
		: Enemy(_health, _texture, _colour, _collision, x, y, faceRight, _LvLManagerHandle) {		
		if (faceRight) states &= Right;
	}
	void Update() override;

private:
	void Move() override;
	//void Brain();
};

