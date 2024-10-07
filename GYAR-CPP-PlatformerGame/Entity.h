#pragma once
#include "Block.h"

class Entity : public Block
{
private:
public:
	bool isGrounded;
	bool isJump = false;
	bool isSkyClear = true;
	short jumpTime = 0;
public:
	Entity(char texture, short colour, short x, short y)
		: Block(texture, colour, x, y) {}
};