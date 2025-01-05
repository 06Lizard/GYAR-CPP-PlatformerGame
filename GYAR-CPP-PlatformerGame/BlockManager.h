#pragma once
#include "Text.h"
//#include "GraphicBase.h"

class BlockManager
{
public:
	// blockMasks
	static const char ground = 'G';
	static const char flag = 'F';
	static const char flagPole = 'f';
private:
	//struct Block {
	//	char texture;
	//	short colour; 
	//	bool isCollision;
	//};
public:
	//Block(char texture, short colour, bool collision) 
	//	: texture(texture), colour(colour), isCollision(collision) {}
	//Block() : texture(' '), colour(0), isCollision(false) {}
	//virtual ~Block() {}

	static bool getCollision(const char& block);
	static char getTexture(const char& block);
	static char getType(const char& block);
	static short getColour(const char& block);
	//virtual void Update();
};