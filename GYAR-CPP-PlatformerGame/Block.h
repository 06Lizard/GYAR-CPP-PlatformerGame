#pragma once
#include "Position.h"
class Block : public Position
{
private:
	// seting of value
	char texture;
	short colour; 
public:
	// getting of value
	// texture colour

	Block(char texture, short colour, Position pos) : texture(texture), colour(colour), Position(pos) {}
	Block(char texture, short colour, short x, short y) : texture(texture), colour(colour), Position(x, y) {}
};

