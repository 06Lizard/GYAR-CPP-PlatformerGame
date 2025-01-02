#pragma once
#include "Text.h"

class Block
{
protected: // need to double check, but able to be changed if something inherits it
	// seting of value
	bool isCollision;
	char texture;
	short colour; 
public:	
	Block(char texture, short colour, bool collision) 
		: texture(texture), colour(colour), isCollision(collision) {}
	Block() : texture(' '), colour(0), isCollision(false) {}
	virtual ~Block() {}

	bool getCollision() const;
	char getTexture() const;
	short getColour() const;
	virtual void Update();	
};