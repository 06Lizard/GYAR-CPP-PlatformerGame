#include "BlockManager.h"

// might need rename

bool BlockManager::getCollision(const char& block)
{
	switch (block)
	{
	case 'G':
		return true;
	default:
		return false;
	}
}

char BlockManager::getTexture(const char& block)
{
	switch (block)
	{
	case 'G':
		return '=';
	case 'F':
		return 'F';
	case 'f':
		return '|';
	default:
		return ' ';
	}
}

short BlockManager::getColour(const char& block)
{
	switch (block)
	{
	case 'G':
		return Text::Green;
	case 'F':
		return Text::BrightRed;
	case 'f':
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
