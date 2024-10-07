#pragma once
#include <windows.h>
#include <chrono>
#include <thread>
#include "Drawing.h"
#include "Player.h"

class PlatformerGame {
private:
	bool running;
	Player player = Player(3, '#', Text::Red, Text::backroundBlack, 0, 0);
public:
	PlatformerGame();

	void Start();

private:
	void Initzialize();
	void Update();
	void Input();
	void Render();
};

