#pragma once
#include "Entity.h"
#include "Text.h"
class Enemy1 : public Entity
{
private:
	static const short HP = 1;
	static const char texture = 'E';
	static const int colour = Text::BrightYellow;
	static const bool collision = false;
public:
	Enemy1(short x, short y, Mapp *mapp, bool faceRight)
		//: Entity(1, 'E', 93, x, y)
		: Entity(HP, texture, colour, collision, x, y, mapp) {
		if (faceRight) states &= Right;
	}
	void Update() override;

private:
	void Move() override;
	//void Brain();
};

