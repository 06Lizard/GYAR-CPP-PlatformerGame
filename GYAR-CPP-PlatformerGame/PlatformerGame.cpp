#include "PlatformerGame.h"

PlatformerGame::PlatformerGame()
{
}

void PlatformerGame::Initzialize() {

}

void PlatformerGame::Start()
{
	Initzialize();
	while (true) 
	{
		Render();
		Input();
		Update();
	}
}

void PlatformerGame::Update()
{
}

void PlatformerGame::Input()
{
}

void PlatformerGame::Render()
{
}

// need work