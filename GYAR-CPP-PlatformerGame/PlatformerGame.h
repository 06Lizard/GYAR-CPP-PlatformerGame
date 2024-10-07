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

	const uint8_t W = 1 << 0; // 0001, sets a one in position 0
	const uint8_t A = 1 << 1; // 0010, sets a one in position 1
	const uint8_t S = 1 << 2; // 0100, sets a one in position 2
	const uint8_t D = 1 << 3; // 1000, sets a one in position 3
	// const uint8_t B = 0 << 3; would set a zero in position 3
	uint8_t movementState; // keps track of the movment state
	
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

	void move(Entity& entity, uint8_t& movementState);
};