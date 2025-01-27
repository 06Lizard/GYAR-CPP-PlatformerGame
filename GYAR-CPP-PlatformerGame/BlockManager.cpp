#include "BlockManager.h"

// might need rename

bool BlockManager::getCollision(const char& block)
{
	switch (block)
	{
	case ground:
		return true;
	default:
		return false;
	}
}

char BlockManager::getTexture(const char& block)
{
	switch (block)
	{
	case ground:
		return '=';
	case flag:
		return 'F';
	case flagPole:
		return '|';
	default:
		return ' ';
	}
}

short BlockManager::getColour(const char& block)
{
	switch (block)
	{
	case ground:
		return Text::Green;
	case flag:
		return Text::BrightRed;
	case flagPole:
		return Text::Gray;
	default:
		return Text::ResetAll;
	}
}

//void BlockManager::Update() {
//	isCollision = false;
//	texture = ' ';
//	colour = 0;
//}
