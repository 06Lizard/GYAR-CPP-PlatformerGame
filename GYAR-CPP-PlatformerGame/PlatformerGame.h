#pragma once
#include "Drawing.h"

class PlatformerGame {
private:
	bool running;

public:
	PlatformerGame();

	void Start();

private:
	void Initzialize();
	void Update();
	void Input();
	void Render();
};

