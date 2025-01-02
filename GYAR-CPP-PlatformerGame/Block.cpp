#include "Block.h"

// might need rename

bool Block::getCollision() const 
{
	return isCollision;
}

char Block::getTexture() const
{
	return texture;
}

short Block::getColour() const
{
	return colour;
}

void Block::Update() {
	isCollision = false;
	texture = ' ';
	colour = 0;
}
