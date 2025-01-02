#include "Enemy1.h"

void Enemy1::Update() {
	//Brain();
	Move();
}

void Enemy1::Move() {
	// is grounded check
	if (!mapp->mapp[x][y + 1]->getCollision()) {
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
		if (x < mapp->width-1 && !mapp->mapp[x + 1][y]->getCollision())
			x++;
		else if (x > 0 && !mapp->mapp[x - 1][y]->getCollision()) {
			states &= ~Right;
			x--;
		}			
	} 
	else if (x > 0 && !mapp->mapp[x - 1][y]->getCollision())
		x--;
	else if (x < mapp->width-1 && !mapp->mapp[x + 1][y]->getCollision()) {
		states |= Right;
		x++;
	}

	states &= ~Down;
	//(x < 0 || x > mapp->width || y < 0 || y > mapp->height) ? destroy() : void();
}