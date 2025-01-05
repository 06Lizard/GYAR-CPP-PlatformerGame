#pragma once
#include <windows.h>
#include "Entity.h" 

class Player : public Entity
{
private:
	static const short _health = 3;
	static const char _texture = '#';
	static const short _colour = Text::Red;
	static const bool _collision = false;
public:
	Player(short x, short y, Mapp *mapp)		
		: Entity(_health, _texture, _colour, _collision, x, y, mapp) {}
	
	short getHealth() const;
	void Update() override;

private: 
	void Move() override;
	void Input();
	void Collision();
};