#pragma once
#include <windows.h>
#include "Entity.h" 
#include "ForwardDeclaredLists.h"

class Player : public Entity
{
private:
	static const short _health = 3;
	static const char _texture = '#';
	static const short _colour = Text::Red;
	static const bool _collision = false;
	LvLManager& _LvLManager;
	
public:
	Player(short x, short y, LvLManager& _LvLManager)
		: Entity(_health, _texture, _colour, _collision, x, y), _LvLManager(_LvLManager) {}
	
	void Update() override;

	void TakeDamage() override { 
		health--;
		if (health < 0)
			_LvLManager.GameOver();
		else _LvLManager.ResetLvL();
	} // tmp, invisibility frames sugested
	void Reset() { health = _health; }

private: 
	void Move() override;
	void Input();
	void Collision();
};