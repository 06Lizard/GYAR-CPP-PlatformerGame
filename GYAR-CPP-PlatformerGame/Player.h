#pragma once
#include "Entity.h" 

class Player : public Entity
{
protected:
	short health;
public:
	Player(short health, char texture, short colour, short x, short y)
		: health(health), Entity(texture, colour, x, y) {}
	short getHealth() const;
};