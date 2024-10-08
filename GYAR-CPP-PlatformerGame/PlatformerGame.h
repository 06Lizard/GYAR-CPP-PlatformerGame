#pragma once
#include <windows.h>
#include <chrono>
#include <thread>
#include "Drawing.h"
#include "Player.h"
#include "Entity.h"

//const int TARGET_FPS = 60;
//const std::chrono::milliseconds TARGET_FRAME_TIME(1000 / TARGET_FPS);  // Time per frame (16 ms for 60 FPS) 

class PlatformerGame {
private:
	bool running;

	Player player = Player(3, '#', Text::Red, 10, 10);
	Entity entity = Entity('?', Text::Blue, 0, 0);	
	Block mapp[64][16];

public:
	PlatformerGame();

	void Start();

private:
	void Initzialize();
	void Update();
	void Render();
	void Input();

private:

	void move(Entity& entity);
};