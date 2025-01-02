#pragma once
#include <windows.h>
#include "Entity.h" 

class Player : public Entity
{
public:
	Player(short health, char texture, short colour, bool collision, short x, short y, Mapp *mapp)		
		: Entity(health, texture, colour, collision, x, y, mapp) {}
	
	short getHealth() const;
	void Update() override;

private: 
	void Move() override;
	void Input();
	void Collision();
};