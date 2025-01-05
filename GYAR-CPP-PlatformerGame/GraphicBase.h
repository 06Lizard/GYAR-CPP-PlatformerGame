#pragma once
class GraphicBase
{
protected:
	bool isCollision;
	char texture;
	short colour;

public:
	GraphicBase(char texture, short colour, bool collision)
		: texture(texture), colour(colour), isCollision(collision) {}
	GraphicBase() : texture(' '), colour(0), isCollision(false) {}
	virtual ~GraphicBase() {}

	bool getCollision();
	char getTexture();
	short getColour();
};

