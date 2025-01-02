#pragma once
#include <chrono>
#include <thread>
#include <vector>
#include "Drawing.h"
#include "Player.h"
#include "Entity.h"
#include "Enemy1.h"
#include "Mapp.h"

//const int TARGET_FPS = 60;
//const std::chrono::milliseconds TARGET_FRAME_TIME(1000 / TARGET_FPS);  // Time per frame (16 ms for 60 FPS) 

class PlatformerGame {
private:
	static const short screenWidth = 32;
	static const short screenHight = 16;	

	bool running;

	Player player = Player(3, '#', Text::Red, false, 10, 10, &mapp);
	Position cameraPos = Position();	
	Mapp mapp;	
	std::vector<Entity*> entities;
	/* test */Enemy1 enemy1 = Enemy1(5, 5, &mapp, false);

	struct Enemy : Entity {
		
	};

public:
	PlatformerGame(): running(true), mapp(&running) {}

	void Start();

private:
	void Initzialize();
	void Update();
	void Render();
	//void _Render(); // replaced with render
	//void Input();

private:

	//void move(Entity& entity); // moved to entities themselves
	void UpdateCamera();
};