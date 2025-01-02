#pragma once
#include "Block.h"

class Flag : public Block {
public:
	Flag() : Block('P', Text::BrightRed, false) {}
	void Update() override;
};

class FlagPole : public Block {
public:
	FlagPole() : Block('|', Text::Gray, false) {}
	void Update() override;
};

