#pragma once
#include <stdint.h>
#include "Mapp.h"
#include "GraphicBase.h"
#include "Position.h"

class Entity : public GraphicBase, public Position
{
protected:
	char texture;

	short health;
	Mapp *mapp;
public:
	// holds Entity's variables / flags
	uint8_t states = 0b00000000;

	// define position of Entity's "bools", and my 2 bit variable
	static const uint8_t Up				= 1 << 0; // 0000 0001
	static const uint8_t Left			= 1 << 1; // 0000 0010
	static const uint8_t Down			= 1 << 2; // 0000 0100
	static const uint8_t Right			= 1 << 3; // 0000 1000
	static const uint8_t isGrounded		= 1 << 4; // 0001 0000
	static const uint8_t isJump			= 1 << 5; // 0010 0000
	static const uint8_t jumpTime		= 0b11000000; // 2 bit variable 

protected:
	virtual void Move() = 0;

public:
	Entity(short health, char texture, short colour, bool collision, short x, short y, Mapp *mapp)
		: health(health), GraphicBase(texture, colour, collision), Position(x, y), mapp(mapp) {}
	virtual ~Entity() {}

	short getHealth() const;
	virtual void Update() = 0;
};