#pragma once
#include "Block.h"

class Entity : public Block
{
private:
public:
	// can add together all these and the movment states into one byte
	bool isGrounded = true;
	bool isSkyClear = true; // remove this to fit jump time and the rest into one nible
	bool isJump = false;
	short jumpTime = 0; // could be turned in to a 2 bit variable
public:
	Entity(char texture, short colour, short x, short y)
		: Block(texture, colour, x, y) {}
};