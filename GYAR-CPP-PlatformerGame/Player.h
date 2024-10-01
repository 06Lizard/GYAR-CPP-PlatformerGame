#pragma once
#include "Block.h"
class Player : public Block
{
private:
	short health;
public:
	Player(short health, char texture, short colour, short backround, short x, short y)
		: health(health), Block(texture, colour, backround, x, y) {}
};