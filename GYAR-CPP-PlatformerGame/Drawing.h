#pragma once
#include "Block.h"
#include "Text.h"
#include <iostream>
class Drawing
{
public: // moreso writing :)
	// sets formatting
	void formatting(bool bold, bool italic, bool underline, bool blink, bool reverse, bool strikethrough);
	//resets formatting
	void formatting(short format);
	// reset all formating, colour, and backround
	void formatting(); // default formatting

public:
	void draw(const Position& pos, char texture, int colour, int backround);
	void draw(Block& block);
};

// should be quite enough