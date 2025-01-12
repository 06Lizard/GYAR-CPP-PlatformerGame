#include "Enemy1.h"

void Enemy1::Update() {
	//Brain();
	Move();
}

void Enemy1::Move() {
	// is grounded check
	if (!BlockManager::getCollision(_LvLManagerHandle.mapp[x][y + 1])) {
		y++; // fall
		states &= ~Down;
		return;
	}	// if we pass here we know we on ground
	else if (!(states & Down)) {
		states |= Down;
		return;
	}// slows down it's move speed to 1/2

	// Right & !Right
	if (states & Right) {
		if (x < LvLManager::width-1 && !BlockManager::getCollision(_LvLManagerHandle.mapp[x + 1][y]))
			x++;
		else if (x > 0 && !BlockManager::getCollision(_LvLManagerHandle.mapp[x - 1][y])) {
			states &= ~Right;
			x--;
		}			
	} 
	else if (x > 0 && !BlockManager::getCollision(_LvLManagerHandle.mapp[x - 1][y]))
		x--;
	else if (x < LvLManager::width-1 && !BlockManager::getCollision(_LvLManagerHandle.mapp[x + 1][y])) {
		states |= Right;
		x++;
	}

	states &= ~Down;
	if (x < 0 || x > LvLManager::width || y < 0 || y > LvLManager::hight) delete this;
}