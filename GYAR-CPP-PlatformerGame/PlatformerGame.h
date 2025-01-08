#pragma once
#include <chrono>
#include <thread>
#include <vector>
#include <conio.h> // allows for _getch witch waits for keypress
#include "Drawing.h"
#include "Player.h"
//#include "LvLManager.h"
//#include "BlockManager.h"

//const int TARGET_FPS = 60;
//const std::chrono::milliseconds TARGET_FRAME_TIME(1000 / TARGET_FPS);  // Time per frame (16 ms for 60 FPS) 

class PlatformerGame {
private:	
	short score = 0;
	bool running;

	Player player;
	Position cameraPos = Position();	
	LvLManager _LvLManager;

public:
	PlatformerGame() : running(true), _LvLManager(running, cameraPos, player), player(10, 10, _LvLManager) {}
	
	void Run();

private:
	void Menue();
	void Initzialize();
	void GameLoop();
	void GameOver();
	void Update();
	void Render();
	//void _Render(); // replaced with render
	//void Input();

private:

	//void move(Entity& entity); // moved to entities themselves
	void UpdateCamera();
};