#pragma once
#include "Drawing.h"

class PlatformerGame {
private:
	bool running;

public:
	PlatformerGame();

	void Start();

private:
	void Update();
	void Input();
	void Render();
};

