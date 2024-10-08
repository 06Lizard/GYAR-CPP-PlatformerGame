#pragma once
#include "Block.h"
#include <stdint.h>

class Entity : public Block
{
private:
public:
	// can add together all these and the movment states into one byte
	//bool isGrounded = true;
	//bool isSkyClear = true; // remove this to fit jump time and the rest into one nible
	//bool isJump = false;
	//short jumpTime = 0; // could be turned in to a 2 bit variable

	// holds Entity's variables / flags
	uint8_t states = 0b00000000;

	// define position of Entity's "bools", and my 2 bit variable
	static const uint8_t W				= 1 << 0; // 0000 0001
	static const uint8_t A				= 1 << 1; // 0000 0010
	static const uint8_t S				= 1 << 2; // 0000 0100
	static const uint8_t D				= 1 << 3; // 0000 1000
	static const uint8_t isGrounded	= 1 << 4; // 0001 0000
	static const uint8_t isJump		= 1 << 5; // 0010 0000
	static const uint8_t jumpTime		= 0b11000000; // 2 bit variable 

public:
	Entity(char texture, short colour, short x, short y)
		: Block(texture, colour, x, y) {}
};