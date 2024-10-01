#pragma once
#include "Position.h"
class Block : public Position
{
protected: // need to double check, but able to be changed if something inherits it
	// seting of value
	char texture;
	short colour; 
	short backround;
public:	
	Block(char texture, short colour, short backround, Position pos) : texture(texture), colour(colour), backround(backround), Position(pos) {}
	Block(char texture, short colour, short backround, short x, short y) : texture(texture), colour(colour),backround(backround), Position(x, y) {}
	
	char getTexture();
	short getColour();
	short getBackround();
};