#pragma once
#include "Position.h"

class Block : public Position
{
protected: // need to double check, but able to be changed if something inherits it
	// seting of value
	char texture;
	short colour; 
public:	
	Block(char texture, short colour, Position pos) : texture(texture), colour(colour), Position(pos) {}
	Block(char texture, short colour, short x, short y) : texture(texture), colour(colour), Position(x, y) {}
	Block() : texture(' '), colour(0), Position(0, 0) {}

	char getTexture() const;
	short getColour() const;
};