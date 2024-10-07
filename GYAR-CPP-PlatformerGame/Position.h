#pragma once
class Position
{
public:
	float x;
	float y;
public:
	Position() : x(0), y(0) {}
	Position(float x, float y) {
		this->x = x;
		this->y = y;
	}	
};

