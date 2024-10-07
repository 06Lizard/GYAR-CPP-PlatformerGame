#pragma once
class Position
{
public:
	short x;
	short y;
public:
	Position() : x(0), y(0) {}
	Position(short x, short y) {
		this->x = x;
		this->y = y;
	}	
};

