#include "Projectile.h"

void Projectile::Update() {
	// check if something is coliding with it rn
	health--;
	Move();
	if (health <= 0)
		delete this;
}

void Projectile::TakeDamage() {
	delete this;
}

void Projectile::Move() {
	if (isRight)
		x++;
	else
		x--;
	if (BlockManager::getCollision(_LvLManagerHandle.mapp[x][y]))
		delete this;
}
