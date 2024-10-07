#include "Drawing.h"

void Drawing::formatting(bool bold, bool italic, bool underline, bool blink, bool reverse, bool strikethrough)
{
	if (bold) std::cout << "\033[1m";
	if (italic) std::cout << "\033[3m";
	if (underline) std::cout << "\033[4m";
	if (blink) std::cout << "\033[5m";
	if (reverse) std::cout << "\033[7m";
	if (strikethrough) std::cout << "\033[9m";
}

void Drawing::formatting(short format)
{
	std::cout << "\033[" << format << "m";
}

void Drawing::formatting()
{
	std::cout << "\033[0m";
}

void Drawing::draw(const Position& pos, char texture, int colour, int backround)
{
	std::cout << "\033[" << pos.y << ";" << pos.x << "H\033[" << colour << "m\033[" << backround << "m" << texture;
}

void Drawing::draw(Block& block)
{
	std::cout << "\033[" << block.y << ";" << block.x << "H\033[" << block.getColour() << "m\033[" << block.getBackround() << "m" << block.getTexture();
}
