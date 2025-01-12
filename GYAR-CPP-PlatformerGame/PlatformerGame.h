#pragma once
#include "ForwardDeclaredLists.h"
//#include "Drawing.h"
#include "Player.h"

//const int TARGET_FPS = 60;
//const std::chrono::milliseconds TARGET_FRAME_TIME(1000 / TARGET_FPS);  // Time per frame (16 ms for 60 FPS) 

class PlatformerGame {
private:	
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
	void Update();
	void Render();	
	void UpdateCamera();
};