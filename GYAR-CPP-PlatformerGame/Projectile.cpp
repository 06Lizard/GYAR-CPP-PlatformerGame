#include "Projectile.h"

void Projectile::Update() {
	// check if something is coliding with it rn
	health--;
	Move();
	//if (health <= 0)
	//	delete this;
}

void Projectile::Move() {
	if (isRight)
		x++;
	else
		x--;
	// check if something is colliding with it rn
}
