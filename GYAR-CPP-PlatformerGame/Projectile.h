#pragma once
#include "Entity.h"

class Projectile : public Entity
{
private:
	const LvLManager::LvLManagerHandle& _LvLManagerHandle;

	static const short _health = 8;
	static const char _texture = '*';
	static const short _colour = Text::BrightYellow;
	static const bool _collision = false;
	
	const bool isRight;

public:
	Projectile(short x, short y, bool isRight, const LvLManager::LvLManagerHandle& _LvLManagerHandle)
		: Entity(_health, _texture, _colour, _collision, x, y), _LvLManagerHandle(_LvLManagerHandle), isRight(isRight) { }

	~Projectile() = default;

	void Update() override;

private:
	void Move() override;
};

